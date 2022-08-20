// vulkan_guide.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <vk_types.h>
#include <vector>
#include <deque>
#include <functional>

struct DeletionQueue {
	std::deque<std::function<void()>> deletors;
	
	void push_function(std::function<void()>&& function) {
		deletors.push_back(function);
	}

	void flush() {
		// reverse iterate the deletion queueu to execute all the functions
		for (auto it = deletors.rbegin(); it != deletors.rend(); it++) {
			(*it)();
		}
		deletors.clear();
	}
};

class VulkanEngine {
public:

	bool _isInitialized{ false };
	int _frameNumber{ 0 };

	VkExtent2D _windowExtent{ 1700 , 900 };

	struct SDL_Window* _window{ nullptr };

	//initializes everything in the engine
	void init();

	//shuts down the engine
	void cleanup();

	//draw loop
	void draw();

	//run main loop
	void run();

	// Vulkan specific
	VkInstance _instance; // Vulkan library
	VkDebugUtilsMessengerEXT _debug_messenger; // Vulkan debug output handle
	VkPhysicalDevice _chosenGPU; // Chosen GPU
	VkDevice _device; // Vulkan device for commands
	VkSurfaceKHR _surface; // Vulkan window surface

	VkSwapchainKHR _swapchain;
	VkFormat _swapchainImageFormat; // image format expected for SDL
	std::vector<VkImage> _swapchainImages; // array of images from swapchain
	std::vector<VkImageView> _swapchainImageViews; // array of image-views from swapchain

	VkQueue _graphicsQueue;
	uint32_t _graphicsQueueFamily;

	VkCommandPool _commandPool;
	VkCommandBuffer _mainCommandBuffer;

	VkRenderPass _renderPass;
	std::vector<VkFramebuffer> _framebuffers;

	VkSemaphore _presentSemaphore, _renderSemaphore;
	VkFence _renderFence;

	VkPipelineLayout _trianglePipelineLayout;
	VkPipeline _redTrianglePipeline;
	VkPipeline _trianglePipeline;

	VmaAllocator _allocator; // vma lib allocator

private:
	void init_vulkan();
	void init_swapchain();
	void init_commands();
	void init_default_renderpass();
	void init_framebuffers();
	void init_sync_structures();
	void init_pipelines();

	bool load_shader_module(const char* filePath, VkShaderModule* outShaderModule);

	int _selectedShader{ 0 };

	DeletionQueue _mainDeletionQueue;
};

class PipelineBuilder {
public:
	std::vector < VkPipelineShaderStageCreateInfo> _shaderStages;
	VkPipelineVertexInputStateCreateInfo _vertexInputInfo;
	VkPipelineInputAssemblyStateCreateInfo _inputAssembly;
	VkViewport _viewport;
	VkRect2D _scissor;
	VkPipelineRasterizationStateCreateInfo _rasterizer;
	VkPipelineColorBlendAttachmentState _colorBlendAttachment;
	VkPipelineMultisampleStateCreateInfo _multisampling;
	VkPipelineLayout _pipelineLayout;

	VkPipeline build_pipeline(VkDevice device, VkRenderPass pass);
};