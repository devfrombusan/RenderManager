cmake_minimum_required(VERSION 3.18.1)

project("RenderManagerTest")


add_library(
        RenderManagerTest
        SHARED

        Jni/Device.cpp
        Jni/Update.cpp

        RenderManager/BdtInfo.cpp
        RenderManager/Mesh.cpp
        RenderManager/Object.cpp
        RenderManager/Layer.cpp
        RenderManager/OtherLayer.cpp
        RenderManager/MeshLayer.cpp
        RenderManager/Shader.cpp
        RenderManager/Collider.cpp
        RenderManager/Camera.cpp
        RenderManager/RenderManager.cpp

        SampleScene/SampleScene.cpp
)


target_link_libraries(
        RenderManagerTest
        log
        GLESv3)