set (CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/bin")

# Add source to this project's executable.
add_executable(
    Vulkan-Engine
    main.cpp
    vk_engine.cpp
    vk_engine.h
    vk_types.h
    vk_initializers.cpp
    vk_initializers.h
    vk_mesh.cpp
    vk_mesh.h
)

### LINKING ###

add_dependencies(Vulkan-Engine Shaders)
target_link_libraries(Vulkan-Engine glfw)
target_link_libraries(Vulkan-Engine Vulkan::Vulkan)
target_link_libraries(Vulkan-Engine glm)
target_link_libraries(Vulkan-Engine vkbootstrap)
target_link_libraries(Vulkan-Engine tinyobjloader)
target_link_libraries(Vulkan-Engine imgui)
target_link_libraries(Vulkan-Engine stb_image)
