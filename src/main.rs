extern crate winit;
#[macro_use]
extern crate serde_json;
extern crate vulkano;

mod core;
mod gfx;

fn main() {
    let mut app = core::application::Application::new();
    app.run();
}
