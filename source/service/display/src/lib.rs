// server/unix/gui_display/src/lib.rs

use std::ffi::CStr;

/// 展示设备详情的函数
#[no_mangle]
pub extern "C" fn show_device_info(device_id: *const libc::c_char, message: *const libc::c_char) {
    let id = unsafe { CStr::from_ptr(device_id).to_string_lossy() };
    let msg = unsafe { CStr::from_ptr(message).to_string_lossy() };

    println!("[RUST UI] 显示设备 {} 的消息: {}", id, msg);

    // TODO: 用 GUI 展示（例如用 egui 弹窗）
}
