extern crate winit;

use std::time::SystemTime;
use core::settings::Settings;

const WINDOW_WIDTH: u32 = 800;
const WINDOW_HEIGHT: u32 = 600;
const APP_NAME: &str = "Origin";

pub struct Application {
    settings: Settings,
    events_loop: winit::EventsLoop,
    window: winit::Window
}

impl Application {
    pub fn new() -> Self {
        let settings = Settings::new();
        let events_loop = winit::EventsLoop::new();
        let mut builder = winit::WindowBuilder::new().with_title(APP_NAME);

        let x;
        let y;
        let mut width = WINDOW_WIDTH;
        let mut height= WINDOW_HEIGHT;

        match settings.window_geometry() {
            None => {
                // Move window on center of screen
                let (monitor_width, monitor_height) = events_loop.get_primary_monitor().get_dimensions();
                x = (monitor_width - width) as i32 / 2;
                y = (monitor_height - height) as i32 / 2;
            }
            Some(settings_geometry) => {
                x = settings_geometry.0;
                y = settings_geometry.1;
                width = settings_geometry.2;
                height = settings_geometry.3;
            }
        }

        // Create window
        builder = builder.with_dimensions(width, height);
        let window = builder.build(&events_loop).unwrap();
        window.set_position(x, y);

        Application { settings, events_loop, window,  }
    }

    pub fn run(&mut self) {
        let mut now = SystemTime::now();
        let mut is_running = true;
        while is_running {
            self.events_loop.poll_events(|event| {
                match event {
                    winit::Event::WindowEvent { event: winit::WindowEvent::Resized(w, h), .. } => {
                        println!("The window was resized to {}x{}", w, h);
                    },
                    winit::Event::WindowEvent { event: winit::WindowEvent::Closed, .. } => {
                        is_running = false;
                    },
                    _ => ()
                }
            });

            let duration = now.elapsed().unwrap();
            const BILLION: u32 = 1000000000;
            let dt = (duration.as_secs() as u32 * BILLION + duration.subsec_nanos()) as f32 / BILLION as f32;
            now = SystemTime::now();

            self.update(dt);
            self.render();
        }
    }

    fn update(&self, _dt: f32) {
//        println!("update: {}", dt)
    }

    fn render(&self) {
//        println!("render")
    }
}

impl Drop for Application {
    fn drop(&mut self) {
        // Write window geometry to settings
        let (x, y) = self.window.get_position().unwrap();
        let (width, height) = self.window.get_inner_size().unwrap();
        self.settings.set_window_geometry(x,y, width, height);
    }
}
