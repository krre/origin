#[macro_use]
extern crate serde_json;

mod core;

fn main() {
    let mut app = core::application::Application::new();
    app.run();
}
