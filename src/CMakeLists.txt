add_executable(origin ${SOURCES} main.cpp
    base/Defines.h
    base/Game.cpp base/Game.h
    base/SDLWrapper.cpp base/SDLWrapper.h
    base/Settings.cpp base/Settings.h
    base/Timer.cpp base/Timer.h
    base/Window.cpp base/Window.h
    debug/Console.h debug/Console.cpp
    debug/DebugEnvironment.h debug/DebugEnvironment.cpp
    debug/DebugHUD.h debug/DebugHUD.cpp
    debug/Logger.h debug/Logger.cpp
    ecs/Component.cpp ecs/Component.h
    ecs/EntityManager.cpp ecs/EntityManager.h
    ecs/Entity.cpp ecs/Entity.h
    ecs/EntityBuilder.cpp ecs/EntityBuilder.h
    ecs/Family.cpp ecs/Family.h
    ecs/System.cpp ecs/System.h
    ecs/components/Components.h
    ecs/components/CameraComponent.h
    ecs/components/LightComponent.h
    ecs/components/MaterialComponent.h
    ecs/components/MovementControllerComponent.h
    ecs/components/MovementComponent.h
    ecs/components/OctreeComponent.h
    ecs/components/PhysicsComponent.h
    ecs/components/RenderComponent.h
    ecs/components/TransformComponent.h
    ecs/systems/CameraSystem.cpp ecs/systems/CameraSystem.h
    ecs/systems/MovementControllerSystem.cpp ecs/systems/MovementControllerSystem.h
    ecs/systems/OctreeSystem.cpp ecs/systems/OctreeSystem.h
    ecs/systems/PhysicsSystem.cpp ecs/systems/PhysicsSystem.h
    ecs/systems/RenderSystem.cpp ecs/systems/RenderSystem.h
    ecs/systems/Systems.h
    ecs/systems/TransformSystem.cpp ecs/systems/TransformSystem.h
    ecs/scenes/GameScene.cpp ecs/scenes/GameScene.h
    ecs/scenes/Scene.cpp ecs/scenes/Scene.h
    event/Event.h event/Event.cpp
    event/Input.h event/Input.cpp
    graphics/Color.cpp graphics/Color.h
    graphics/Mesh.cpp graphics/Mesh.h
    graphics/Plane.cpp graphics/Plane.h
    graphics/light/Light.cpp graphics/light/Light.h
    graphics/render/DebugRenderer.cpp graphics/render/DebugRenderer.h
    graphics/render/OctreeRenderer.cpp graphics/render/OctreeRenderer.h
    graphics/render/PolygonalOctreeRenderer.cpp graphics/render/PolygonalOctreeRenderer.h
    graphics/render/RaycastOctreeRenderer.cpp graphics/render/RaycastOctreeRenderer.h
    graphics/render/Renderer.cpp graphics/render/Renderer.h
    graphics/render/RenderManager.cpp graphics/render/RenderManager.h
    graphics/render/SceneRenderer.cpp graphics/render/SceneRenderer.h
    graphics/render/View3DBatch.cpp graphics/render/View3DBatch.h
    graphics/render/UIRenderer.cpp graphics/render/UIRenderer.h
    graphics/voxel/GPUMemoryManager.cpp graphics/voxel/GPUMemoryManager.h
    graphics/voxel/SVOBuilder.cpp graphics/voxel/SVOBuilder.h
    graphics/voxel/primitive/Cone.cpp graphics/voxel/primitive/Cone.h
    graphics/voxel/primitive/Cube.cpp graphics/voxel/primitive/Cube.h
    graphics/voxel/primitive/Sphere.cpp graphics/voxel/primitive/Sphere.h
    process/Process.h process/Process.cpp
    process/ProcessManager.h process/ProcessManager.cpp
    resource/Resource.h resource/Resource.cpp
    resource/ResourceManager.h resource/ResourceManager.cpp
    screen/GameScreen.cpp screen/GameScreen.h
    screen/LoadWorldScreen.cpp screen/LoadWorldScreen.h
    screen/MenuScreen.cpp screen/MenuScreen.h
    screen/NewWorldScreen.cpp screen/NewWorldScreen.h
    screen/Screen.cpp screen/Screen.h
    screen/SettingsScreen.cpp screen/SettingsScreen.h
    screen/WaitScreen.cpp screen/WaitScreen.h
    ui/Button.cpp ui/Button.h
    ui/Control.cpp ui/Control.h
    ui/Font.cpp ui/Font.h
    ui/Label.cpp ui/Label.h
    ui/Layout.cpp ui/Layout.h
    ui/LinearLayout.cpp ui/LinearLayout.h
    ui/ListBox.cpp ui/ListBox.h
    ui/Overlay.cpp ui/Overlay.h
    ui/Rectangle.cpp ui/Rectangle.h
    ui/SDFFont.cpp ui/SDFFont.h
    ui/TextEdit.cpp ui/TextEdit.h
    ui/Toast.cpp ui/Toast.h
    ui/UIBatch.cpp ui/UIBatch.h
    ui/UIManager.cpp ui/UIManager.h
    ui/View3D.cpp ui/View3D.h
    ui/dialog/Dialog.h ui/dialog/Dialog.cpp
    ui/dialog/PauseDialog.h ui/dialog/PauseDialog.cpp
    world/Earth.cpp world/Earth.h
    world/ProceduralObject.cpp world/ProceduralObject.h
    world/World.cpp world/World.h
)

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
