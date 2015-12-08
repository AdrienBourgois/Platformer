#include <typeinfo>

#include "device.h"
#include "window.h"
#include "txtLogger.h"
#include "meshSceneNode.h"
#include "cameraSceneNode.h"
#include "imgui.h"
#include "imgui_impl.h"
#include "guiDebugWindow.h"
#include "guiOpenFile.h"
#include "driver.h"
#include "fileUtility.h"
#include "maths/utility.h"
#include "maths/polyhedron.h"
#include "maths/collider.h"
#include "maths/colliderManager.h"

int main()
{
    id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);

    std::unique_ptr<id::Device> device = device->create();
    
    auto mesh = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "cube", "pos3d_tex2d", "", id::maths::Shape::cube);
    auto mesh2 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "cube", "pos3d_tex2d", "", id::maths::Shape::cube);
    mesh->setPosition({0,15,40});
    mesh2->setPosition({3,13.5,40});

    id::maths::ColliderManager colMgr;
    colMgr.addCollider(mesh, "cube1");
    colMgr.addCollider(mesh2, "cube2");

    id::scene::CameraSceneNode* cam = id::scene::CameraSceneNode::createCameraSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "Cam", 45.f, 1280.f/720.f, 0.1f, 1000.f);
    cam->setPosition({0.f, 15.f,50.f});
    (void)cam;

    id::DebugWindow* debug_window = new id::DebugWindow();
    id::OpenFile* open_file = new id::OpenFile();
    
    while (device->run())
    {
        device->getDriver()->clear();
        device->getSceneManager()->draw();
        id::imgui_impl::NewFrame(device.get());
        
        debug_window->Display(device.get());
        open_file->Display(device.get());

        //std::vector<std::pair<std::string, std::string>> collisions = colMgr.checkAllColisions();

        //for (unsigned int i = 0; i < collisions.size(); ++i)
        //{
        //    std::cout << "Collision entre " << collisions[i].first << " et " << collisions[i].second << std::endl;
        //}

        ImGui::Render();
        device->getWindow()->swap();
    }

    ImGui::Shutdown();
    
    delete debug_window;
    delete open_file;
    
    return EXIT_SUCCESS;
}
