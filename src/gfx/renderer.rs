use gfx::surface_adapter;
use vulkano::command_buffer::AutoCommandBufferBuilder;
use vulkano::device::Device;
use vulkano::device::DeviceExtensions;
use vulkano::device::Queue;
use vulkano::framebuffer::Framebuffer;
use vulkano::framebuffer::FramebufferAbstract;
use vulkano::framebuffer::RenderPassAbstract;
use vulkano::image::swapchain::SwapchainImage;
use vulkano::image::ImageUsage;
use vulkano::instance::Instance;
use vulkano::instance::PhysicalDevice;
use vulkano::swapchain;
use vulkano::swapchain::AcquireError;
use vulkano::swapchain::PresentMode;
use vulkano::swapchain::Surface;
use vulkano::swapchain::SurfaceTransform;
use vulkano::swapchain::Swapchain;
use vulkano::sync::now;
use vulkano::sync::GpuFuture;
use winit;

use std::mem;
use std::sync::Arc;

pub struct Renderer {
    vulkan_backend: VulkanBackend,
}

struct VulkanBackend {
    instance: Arc<Instance>,
    surface: Arc<Surface>,
    device: Arc<Device>,
    queue: Arc<Queue>,
    swapchain: Arc<Swapchain>,
    swapchain_images: Vec<Arc<SwapchainImage>>,
    framebuffers: Option<Vec<Arc<dyn FramebufferAbstract + Send + Sync>>>,
    render_pass: Arc<dyn RenderPassAbstract + Send + Sync>,
    recreate_swapchain: bool,
    previous_frame_end: Box<dyn GpuFuture>,
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

        self.vulkan_backend.previous_frame_end.cleanup_finished();

        let (image_num, acquire_future) =
            match swapchain::acquire_next_image(self.vulkan_backend.swapchain.clone(), None) {
                Ok(r) => r,
                Err(AcquireError::OutOfDate) => {
                    self.vulkan_backend.recreate_swapchain = true;
                    return;
                }
                Err(err) => panic!("{:?}", err),
            };

        let command_buffer = AutoCommandBufferBuilder::primary_one_time_submit(
            self.vulkan_backend.device.clone(),
            self.vulkan_backend.queue.family(),
        )
        .unwrap()
        .begin_render_pass(
            self.vulkan_backend.framebuffers.as_ref().unwrap()[image_num].clone(),
            false,
            vec![[0.0, 0.0, 1.0, 1.0].into()],
        )
        .unwrap()
        .end_render_pass()
        .unwrap()
        .build()
        .unwrap();

        //        let future = self.vulkan_backend.previous_frame_end.join(acquire_future)
        //            .then_execute(self.vulkan_backend.queue.clone(), command_buffer).unwrap()
        //            .then_swapchain_present(self.vulkan_backend.queue.clone(), self.vulkan_backend.swapchain.clone(), image_num)
        //            .then_signal_fence_and_flush().unwrap();
        //        self.vulkan_backend.previous_frame_end = Box::new(future) as Box<_>;

        //        println!("render")
    }
}

impl VulkanBackend {
    pub fn new(window: &winit::Window) -> Self {
        let instance = Instance::new(None, &surface_adapter::required_extensions(), None)
            .expect("Failed to create Vulkan instance");

        let surface = surface_adapter::build_surface(&window, instance.clone()).unwrap();

        let physical = PhysicalDevice::enumerate(&instance)
            .next()
            .expect("No device available");
        // Some little debug infos.
        println!(
            "Using device: {} (type: {:?})",
            physical.name(),
            physical.ty()
        );

        let queue = physical
            .queue_families()
            .find(|&q| q.supports_graphics() && surface.is_supported(q).unwrap_or(false))
            .expect("Couldn't find a graphical queue family");

        let (device, mut queues) = {
            let device_ext = DeviceExtensions {
                khr_swapchain: true,
                ..DeviceExtensions::none()
            };

            Device::new(
                physical,
                physical.supported_features(),
                &device_ext,
                [(queue, 0.5)].iter().cloned(),
            )
            .expect("Failed to create device")
        };

        let queue = queues.next().unwrap();

        let (swapchain, swapchain_images) = {
            let caps = surface
                .capabilities(physical)
                .expect("Failed to get surface capabilities");

            let alpha = caps.supported_composite_alpha.iter().next().unwrap();
            let format = caps.supported_formats[0].0;

            let dimensions = {
                let (width, height) = window.get_inner_size().unwrap();
                [width, height]
            };

            let usage = ImageUsage {
                color_attachment: true,
                ..ImageUsage::none()
            };

            Swapchain::new(
                device.clone(),
                surface.clone(),
                caps.min_image_count,
                format,
                dimensions,
                1,
                usage,
                &queue,
                SurfaceTransform::Identity,
                alpha,
                PresentMode::Fifo,
                true,
                None,
            )
            .expect("Failed to create swapchain")
        };

        let framebuffers: Option<Vec<Arc<dyn FramebufferAbstract + Send + Sync>>> = None;

        let render_pass = Arc::new(
            single_pass_renderpass!(device.clone(),
                attachments: {
                    color: {
                        load: Clear,
                        store: Store,
                        format: swapchain.format(),
                        samples: 1,
                    }
                },
                pass: {
                    color: [color],
                    depth_stencil: {}
                }
            )
            .unwrap(),
        );

        let previous_frame_end = Box::new(now(device.clone())) as Box<dyn GpuFuture>;

        VulkanBackend {
            instance: instance.clone(),
            surface,
            device,
            queue,
            swapchain,
            swapchain_images,
            framebuffers,
            render_pass,
            recreate_swapchain: true,
            previous_frame_end,
        }
    }

    fn resize_swapchain(&mut self) {
        let capabilites = self
            .surface
            .capabilities(self.device.physical_device())
            .unwrap();
        let dimensions = capabilites.current_extent.unwrap();
        println!("{} {}", dimensions[0], dimensions[1]);

        let (new_swapchain, new_images) = match self.swapchain.recreate_with_dimension(dimensions) {
            Ok(r) => r,
            Err(err) => panic!("{:?}", err),
        };

        mem::replace(&mut self.swapchain, new_swapchain);
        mem::replace(&mut self.swapchain_images, new_images);

        let new_framebuffers = Some(
            self.swapchain_images
                .iter()
                .map(|image| {
                    Arc::new(
                        Framebuffer::start(self.render_pass.clone())
                            .add(image.clone())
                            .unwrap()
                            .build()
                            .unwrap(),
                    ) as Arc<dyn FramebufferAbstract + Send + Sync>
                })
                .collect::<Vec<_>>(),
        );
        mem::replace(&mut self.framebuffers, new_framebuffers);
    }
}
