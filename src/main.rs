extern crate winit;

fn main() {
    let mut events_loop = winit::EventsLoop::new();
    let _window = winit::Window::new(&events_loop).unwrap();

    events_loop.run_forever(|event| {
        match event {
            winit::Event::WindowEvent { event: winit::WindowEvent::Closed, .. } => {
                winit::ControlFlow::Break
            },
            _ => winit::ControlFlow::Continue,
        }
    });
}
