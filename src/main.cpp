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

int main(int argc, char* argv[])
{
	id::TXTLogger::getInstance()->setLogLevel(id::LL_ALL);

	std::unique_ptr<id::Device> device = device->create();
	
	if (argc > 1)
	{
		id::scene::MeshSceneNode* mesh_scn = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), id::FileUtility::getFileNameFromPath(argv[1]), "pos3d_tex2d", argv[1]);
		(void) mesh_scn;
	}

    std::vector<GLfloat> triangle{
        0.0f, 0.0f, 0.0f,       0.f, 1.f,       0.f, 0.f, 0.f,
        1.0f,-0.5f, 0.0f,       0.f, 0.f,       0.f, 0.f, 0.f,
        1.0f, 0.5f, 0.0f,       1.f, 0.f,       0.f, 0.f, 0.f,
    };
    
	auto mesh = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "cube", "pos3d_tex2d", "", id::maths::Shape::cube);
    auto mesh2 = id::scene::MeshSceneNode::createMeshSceneNode(device->getSceneManager(), device->getSceneManager()->getRootNode(), "cube", "pos3d_tex2d", "", id::maths::Shape::cube);
	mesh->setPosition({2,15,40});
	mesh2->setPosition({3,13.5,40});


	std::vector<id::maths::Vector3> points         = id::maths::getPointsFromVectorFloat(triangle);
	std::vector<id::maths::Vector3> newPointsMesh  = id::maths::calCoordFromMatrix(points, mesh->AbsoluteTransformation());
	std::vector<id::maths::Vector3> newPointsMesh2 = id::maths::calCoordFromMatrix(points, mesh2->AbsoluteTransformation());

	id::maths::Polyhedron polyhedron(newPointsMesh);
	id::maths::Polyhedron polyhedron2(newPointsMesh2);

	id::maths::Collider polyhedronCollider(polyhedron);
	id::maths::Collider polyhedronCollider2(polyhedron2);




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

	newPointsMesh  = id::maths::calCoordFromMatrix(points, mesh->AbsoluteTransformation());
	newPointsMesh2 = id::maths::calCoordFromMatrix(points, mesh2->AbsoluteTransformation());
	polyhedronCollider.getPolyhedron().setPoints(newPointsMesh);
	polyhedronCollider2.getPolyhedron().setPoints(newPointsMesh2);

    polyhedronCollider.updateBoundingBox();
    polyhedronCollider2.updateBoundingBox();

 		ImGui::Render();
		device->getWindow()->swap();

        if (polyhedronCollider.collide(polyhedronCollider2))
            std::cout << "collision" << std::endl;
        else
        	std::cout << "pas de collision" << std::endl;
	}

	ImGui::Shutdown();
	
	delete debug_window;
	delete open_file;
	
	return EXIT_SUCCESS;
}
