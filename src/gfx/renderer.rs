use winit;
use gfx::surface_adapter;
use vulkano::instance::Instance;
use vulkano::instance::PhysicalDevice;
use vulkano::swapchain::Surface;
use vulkano::device::DeviceExtensions;
use vulkano::device::Device;
use vulkano::swapchain;
use vulkano::swapchain::PresentMode;
use vulkano::swapchain::SurfaceTransform;
use vulkano::swapchain::Swapchain;
use vulkano::swapchain::AcquireError;
use vulkano::swapchain::SwapchainCreationError;
use vulkano::sync::now;
use vulkano::sync::SharingMode;
use vulkano::sync::GpuFuture;
use vulkano::image::ImageUsage;
use vulkano::image::swapchain::SwapchainImage;

use std::sync::Arc;

pub struct Renderer {
    vulkan_backend: VulkanBackend
}

struct VulkanBackend {
    instance: Arc<Instance>,
    surface: Arc<Surface>,
    device: Arc<Device>,
    swapchain: Arc<Swapchain>,
    swapchain_images: Vec<Arc<SwapchainImage>>,
    recreate_swapchain: bool
}

impl Renderer {
    pub fn new(window: &winit::Window) -> Self {
        let mut vulkan_backend = VulkanBackend::new(&window);
        vulkan_backend.resize_swapchain();

        Renderer { vulkan_backend }
    }

    pub fn render(&mut self) {
        if self.vulkan_backend.recreate_swapchain {
            println!("recreate swapchain");
            self.vulkan_backend.resize_swapchain();

            self.vulkan_backend.recreate_swapchain = false;
        }
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

        let queue = physical.queue_families().find(|&q| {
            q.supports_graphics() && surface.is_supported(q).unwrap_or(false)
        }).expect("Couldn't find a graphical queue family");

        let (device, mut queues) = {
            let device_ext = DeviceExtensions {
                khr_swapchain: true,
                .. DeviceExtensions::none()
            };

            Device::new(physical, physical.supported_features(), &device_ext,
                        [(queue, 0.5)].iter().cloned()).expect("Failed to create device")
        };

        let queue = queues.next().unwrap();

        let (mut swapchain, mut swapchain_images) = {
            let caps = surface.capabilities(physical)
                .expect("Failed to get surface capabilities");

            let alpha = caps.supported_composite_alpha.iter().next().unwrap();
            let format = caps.supported_formats[0].0;

            let mut dimensions = {
                let (width, height) = window.get_inner_size().unwrap();
                [width, height]
            };

            let usage = ImageUsage {
                color_attachment: true,
                .. ImageUsage::none()
            };

            Swapchain::new(device.clone(), surface.clone(), caps.min_image_count, format,
                           dimensions, 1, usage, &queue,
                           SurfaceTransform::Identity, alpha, PresentMode::Fifo, true, None)
                .expect("Failed to create swapchain")

        };

        VulkanBackend {
            instance: instance.clone(),
            surface,
            device,
            swapchain,
            swapchain_images,
            recreate_swapchain: true
        }
    }

    fn resize_swapchain(&mut self) {

    }
}
