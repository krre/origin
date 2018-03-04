extern crate winit;

#[macro_use]
extern crate serde_json;

use std::fs::File;
use std::io::{Write, Read, BufReader};
use std::env;

fn main() {
    // Get path to settings file
    let current_exe = env::current_exe().unwrap();
    let mut settings_path = current_exe.parent().unwrap().to_path_buf();
    settings_path.push("origin.ini");

    // Create window
    let mut events_loop = winit::EventsLoop::new();
    let mut builder = winit::WindowBuilder::new().with_title("Origin");

    let mut x = i32::max_value();
    let mut y = i32::max_value();

    // Read settings
    match File::open(&settings_path) {
        Ok(file) => {
            let mut buf = BufReader::new(file);
            let mut data = String::new();
            buf.read_to_string(&mut data).unwrap();

            let settings: serde_json::Value = serde_json::from_str(data.as_str()).unwrap();
            x = settings["window"]["x"].as_i64().unwrap() as i32;
            y = settings["window"]["y"].as_i64().unwrap() as i32;
            let width = settings["window"]["width"].as_i64().unwrap();
            let height = settings["window"]["height"].as_i64().unwrap();
            builder = builder.with_dimensions(width as u32, height as u32);
        },
        Err(_) => {}
    };

    let window = builder.build(&events_loop).unwrap();

    if x == i32::max_value() || y == i32::max_value() {
        // Move window on center of screen
        let (monitor_width, monitor_height) = events_loop.get_primary_monitor().get_dimensions();
        let (window_width, window_height) = window.get_outer_size().unwrap();

        x = (monitor_width - window_width) as i32 / 2;
        y = (monitor_height - window_height) as i32 / 2;
    }

    window.set_position(x, y);

    events_loop.run_forever(|event| {
        match event {
            winit::Event::WindowEvent { event: winit::WindowEvent::Closed, .. } => {
                winit::ControlFlow::Break
            },
            _ => winit::ControlFlow::Continue,
        }
    });

    // Write window geometry to settings
    let (window_x, window_y) = window.get_position().unwrap();
    let (window_width, window_height) = window.get_outer_size().unwrap();

    let settings = json!({
        "window": {
            "x": window_x,
            "y": window_y,
            "width": window_width,
            "height": window_height
        }
    });

    let _file = File::create(settings_path).unwrap().write_all(settings.to_string().as_bytes());
}
