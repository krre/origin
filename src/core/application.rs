extern crate winit;

use core::settings::Settings;

pub struct Application {
    settings: Settings,
    events_loop: winit::EventsLoop,
    window: winit::Window
}

impl Application {
    pub fn new() -> Self {
        let settings = Settings::new();
        let (mut x, mut y, width, height) = settings.window_geometry();

        // Create window
        let events_loop = winit::EventsLoop::new();
        let mut builder = winit::WindowBuilder::new().with_title("Origin");

        if x != i32::max_value() {
            builder = builder.with_dimensions(width, height);
        }

        let window = builder.build(&events_loop).unwrap();

        if x == i32::max_value() {
            // Move window on center of screen
            let (monitor_width, monitor_height) = events_loop.get_primary_monitor().get_dimensions();
            let (window_width, window_height) = window.get_outer_size().unwrap();

            x = (monitor_width - window_width) as i32 / 2;
            y = (monitor_height - window_height) as i32 / 2;
        }

        window.set_position(x, y);

        Application { settings, events_loop, window,  }
    }

    pub fn run(&mut self) {
        self.events_loop.run_forever(|event| {
            match event {
                winit::Event::WindowEvent { event: winit::WindowEvent::Closed, .. } => {
                    winit::ControlFlow::Break
                },
                _ => winit::ControlFlow::Continue,
            }
        });
    }
}

impl Drop for Application {
    fn drop(&mut self) {
        // Write window geometry to settings
        let (x, y) = self.window.get_position().unwrap();
        let (width, height) = self.window.get_outer_size().unwrap();

        self.settings.set_window_geometry(x,y, width, height);
    }
}
