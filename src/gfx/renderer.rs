use vulkano_win;
use vulkano::instance::Instance;

use std::sync::Arc;

pub struct Renderer {
    vulkan_backend: VulkanBackend
}

struct VulkanBackend {
    instance: Arc<Instance>
}

impl Renderer {
    pub fn new() -> Self {
        let vulkan_backend = VulkanBackend::new();

        Renderer { vulkan_backend }
    }

    pub fn render(&self) {
//        println!("render")
    }
}

impl VulkanBackend {
    pub fn new() -> Self {
        let instance = Instance::new(None, &vulkano_win::required_extensions(), None)
            .expect("Failed to create Vulkan instance");

        VulkanBackend { instance }
    }
}
