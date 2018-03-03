extern crate winit;

use std::fs::File;
use std::io::Write;
use std::env;

fn main() {
    let current_exe = env::current_exe().unwrap();
    let mut settings_path = current_exe.parent().unwrap().to_path_buf();
    settings_path.push("origin.ini");

    let mut events_loop = winit::EventsLoop::new();
    let window = winit::Window::new(&events_loop).unwrap();
    window.set_title("Origin");

    let (monitor_width, monitor_height) = events_loop.get_primary_monitor().get_dimensions();
    let (window_width, window_height) = window.get_outer_size().unwrap();

    let x = (monitor_width - window_width) / 2;
    let y = (monitor_height - window_height) / 2;

    window.set_position(x as i32, y as i32);

    events_loop.run_forever(|event| {
        match event {
            winit::Event::WindowEvent { event: winit::WindowEvent::Closed, .. } => {
                winit::ControlFlow::Break
            },
            _ => winit::ControlFlow::Continue,
        }
    });

    let _file = File::create(settings_path).unwrap().write_all(b"Hello, world!");
}
