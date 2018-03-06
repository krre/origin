use winit;
use gfx::surface_adapter;
use vulkano::instance::Instance;
use vulkano::instance::PhysicalDevice;
use vulkano::swapchain::Surface;

use std::sync::Arc;

pub struct Renderer {
    vulkan_backend: VulkanBackend
}

struct VulkanBackend {
    instance: Arc<Instance>,
    surface: Arc<Surface>
}

impl Renderer {
    pub fn new(window: &winit::Window) -> Self {
        let vulkan_backend = VulkanBackend::new(&window);

        Renderer { vulkan_backend }
    }

    pub fn render(&self) {
//        println!("render")
    }
}

impl VulkanBackend {
    pub fn new(window: &winit::Window) -> Self {
        let instance = Instance::new(None, &surface_adapter::required_extensions(), None)
            .expect("Failed to create Vulkan instance");

        let surface = surface_adapter::build_surface(&window, instance.clone()).unwrap();

        let physical = PhysicalDevice::enumerate(&instance).next()
            .expect("No device available");
        // Some little debug infos.
        println!("Using device: {} (type: {:?})", physical.name(), physical.ty());

        VulkanBackend {
            instance: instance.clone(),
            surface
        }
    }
}
