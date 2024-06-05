add_subdirectory(base)
add_subdirectory(debug)
add_subdirectory(ecs)
add_subdirectory(event)
add_subdirectory(graphics)
add_subdirectory(process)
add_subdirectory(resource)
add_subdirectory(screen)
add_subdirectory(ui)
add_subdirectory(world)

add_executable(origin ${SOURCES} main.cpp)

target_link_libraries(origin
    ${SDL2_LIBRARY}
    ${FREETYPE_LIBRARIES}
    ${BULLET_LIBRARIES}
    stdc++fs
    core
    vulkan-o
    octree
)

if(UNIX)
    target_link_libraries(origin
        png
        z # zlib
    )
endif()
