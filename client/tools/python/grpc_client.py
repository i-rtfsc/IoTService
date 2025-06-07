import grpc
import signal
import threading
import time

import iot_service_pb2
import iot_service_pb2_grpc


class IoTClientWatchdog:
    """
    IoT gRPC客户端管理类，包含心跳流的守护，
    并支持同步调用 sendCommand 和 reportStatus。
    """

    def __init__(self, server_addr, device_id, user_id, auth_token,
                 heartbeat_interval=2, retry_delay=3):
        self.server_addr = server_addr
        self.device_id = device_id
        self.user_id = user_id
        self.auth_token = auth_token
        self.heartbeat_interval = heartbeat_interval
        self.retry_delay = retry_delay

        self._channel = None
        self._stub = None
        self._heartbeat_call = None
        self._heartbeat_thread = None
        self._stop_event = threading.Event()

    def _create_channel_and_stub(self):
        self._channel = grpc.insecure_channel(self.server_addr)
        self._stub = iot_service_pb2_grpc.IoTServiceStub(self._channel)

    def send_command(self):
        """
        同步调用发送命令接口
        """
        print(">>> Sending SendCommand Request")
        request = iot_service_pb2.DeviceCommand(
            device_id=self.device_id,
            command="reboot",
            params={"mode": "safe"},
            user_id=self.user_id,
            auth_token=self.auth_token,
            timestamp=int(time.time())
        )
        try:
            response = self._stub.sendCommand(request)
            print("SendCommand Response:", response)
        except grpc.RpcError as e:
            print(f"[sendCommand] gRPC error: {e.code()} - {e.details()}")

    def report_status(self):
        """
        同步调用设备状态上报接口
        """
        print(">>> Sending ReportStatus Request")
        request = iot_service_pb2.DeviceStatus(
            device_id=self.device_id,
            status="online",
            details={"temp": "36.5"},
            user_id=self.user_id,
            auth_token=self.auth_token,
            timestamp=int(time.time())
        )
        try:
            response = self._stub.reportStatus(request)
            print("ReportStatus Response:", response)
        except grpc.RpcError as e:
            print(f"[reportStatus] gRPC error: {e.code()} - {e.details()}")

    def _heartbeat_generator(self):
        while not self._stop_event.is_set():
            yield iot_service_pb2.HeartbeatRequest(
                device_id=self.device_id,
                user_id=self.user_id,
                auth_token=self.auth_token,
                timestamp=int(time.time())
            )
            time.sleep(self.heartbeat_interval)

    def _run_heartbeat(self):
        while not self._stop_event.is_set():
            try:
                self._create_channel_and_stub()
                print("[Heartbeat] Starting heartbeat stream...")
                self._heartbeat_call = self._stub.heartbeat(self._heartbeat_generator())

                for ack in self._heartbeat_call:
                    if self._stop_event.is_set():
                        break
                    print(f"[Heartbeat] Ack received: code={ack.code}, message={ack.message}")

            except grpc.RpcError as e:
                print(f"[Heartbeat] gRPC error: {e.code()} - {e.details()}")
            except Exception as ex:
                print(f"[Heartbeat] Exception: {ex}")
            finally:
                print(f"[Heartbeat] Disconnected. Retrying in {self.retry_delay} seconds...")
                time.sleep(self.retry_delay)

    def start(self):
        if self._heartbeat_thread and self._heartbeat_thread.is_alive():
            print("[Client] Already running")
            return
        self._stop_event.clear()

        self._create_channel_and_stub()

        # 先发送命令和状态上报，初始化业务
        self.send_command()
        self.report_status()

        self._heartbeat_thread = threading.Thread(target=self._run_heartbeat, daemon=True)
        self._heartbeat_thread.start()
        print("[Client] Started")

    def stop(self):
        print("[Client] Stopping...")
        self._stop_event.set()
        if self._heartbeat_call:
            try:
                self._heartbeat_call.cancel()
            except Exception:
                pass
        if self._heartbeat_thread:
            self._heartbeat_thread.join()
        if self._channel:
            self._channel.close()
        print("[Client] Stopped")


# ---- 主程序 ----

def main():
    stop_event = threading.Event()

    def signal_handler(sig, frame):
        print("\n>>> Signal received, shutting down...", flush=True)
        stop_event.set()

    signal.signal(signal.SIGINT, signal_handler)
    signal.signal(signal.SIGTERM, signal_handler)

    client = IoTClientWatchdog(
        server_addr="localhost:50051",
        device_id="device123",
        user_id="user42",
        auth_token="token123",
        heartbeat_interval=1,
        retry_delay=2
    )

    client.start()

    try:
        print(">>> Client running. Press Ctrl+C to stop.", flush=True)
        while not stop_event.is_set():
            time.sleep(0.1)  # 更短的 sleep 提高响应速度
    except KeyboardInterrupt:
        print(">>> KeyboardInterrupt caught in main thread", flush=True)
        stop_event.set()
    finally:
        client.stop()
        print(">>> Client exited gracefully", flush=True)


if __name__ == '__main__':
    main()
