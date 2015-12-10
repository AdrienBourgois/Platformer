#include <SDL2/SDL.h>
#include <iostream>

#include "guiDebugWindow.h"
#include "imgui_impl.h"
#include "imgui.h"
#include "sceneNode.h"
#include "meshSceneNode.h"
#include "mesh.h"
#include "cameraSceneNode.h"
#include "device.h"
#include "maths/vector.h"
#include "window.h"
#include "guiEditMaterialWindow.h"
#include "guiLogger.h"

namespace id {

DebugWindow::DebugWindow()
: GUI_Window(true)
{
	_edit_material_window = new EditMaterialWindow();
	_guiLogger = new DebugLogger();
}

DebugWindow::~DebugWindow()
{
	delete _edit_material_window;
	delete _guiLogger;
}

auto DebugWindow::Display(Device* dev) -> void
{
	SDL_assert(dev);

	float height = dev->getWindow()->getHeight();
	float width  = dev->getWindow()->getWidth();	
	_edit_material_window->Display(dev);

	ImGui::SetNextWindowPos({0, height*1/10}, 2);
	
	ImGui::Begin("Nodes", &_visible, {width*1/4, height*1/3});

	DisplayNodesTree(dev->getSceneManager()->getRootNode());

	ImGui::End();
}

auto DebugWindow::DisplayNodesTree(scene::SceneNode* node) -> void
{
	SDL_assert(node);

		if (ImGui::TreeNode(node, "%s", node->getName().c_str()))
	{
		if (node != (node->getScene()->getRootNode()))
		{
			maths::Vector3 node_pos = node->getPosition();
			if (ImGui::DragFloat3("Position", (float*)&node_pos.val, 0.25f, 0.f, 0.f, "%.2f", 1.f))
			{
				node->setPosition(node_pos);
			}
			
			maths::Vector3 node_rot = node->getRotation();
			if (ImGui::DragFloat3("Rotation", (float*)&node_rot.val, 0.25f, 0.f, 0.f, "%.2f", 1.f))
			{
				node->setRotation(node_rot);
			}

			maths::Vector3 node_sca = node->getScale();
			if (ImGui::DragFloat3("Scale", (float*)&node_sca.val, 0.25f, 0.f, 0.f, "%.2f", 1.f))
			{
				node->setScale(node_sca);
			}
		}
		if (node == ((scene::SceneNode*)(node->getScene()->getActiveCamera())))
		{
			float cam_fovy = ((scene::CameraSceneNode*)(node))->getFOV();
			if (ImGui::DragFloat("FOV", &cam_fovy, 0.25f, 0.f, 0.f, "%.2f", 1.f))
				((scene::CameraSceneNode*)(node))->setFOV(cam_fovy);
			float cam_ratio = ((scene::CameraSceneNode*)(node))->getRatio();
			if (ImGui::DragFloat("Ratio", &cam_ratio, 0.01f, 0.f, 0.f, "%.2f", 1.f))
				((scene::CameraSceneNode*)(node))->setRatio(cam_ratio);
			float cam_near = ((scene::CameraSceneNode*)(node))->getNear();
			if (ImGui::DragFloat("Near", &cam_near, 0.001f, 0.f, 0.f, "%.3f", 1.f))
				((scene::CameraSceneNode*)(node))->setNear(cam_near);
			float cam_far = ((scene::CameraSceneNode*)(node))->getFar();
			if (ImGui::DragFloat("Far", &cam_far, 0.25f, 0.f, 0.f, "%.2f", 1.f))
				((scene::CameraSceneNode*)(node))->setFar(cam_far);
		}
	
		if (node != node->getScene()->getRootNode() && node != static_cast<scene::CameraSceneNode*>(node)->getScene()->getActiveCamera())
		{
			ImGui::Text("Vertex 		 : %d", static_cast<scene::MeshSceneNode*>(node)->getMesh()->getVertex());
			ImGui::Text("Triangle		: %d", static_cast<scene::MeshSceneNode*>(node)->getMesh()->getTriangle());
			ImGui::Text("TextureCoord	: %d", static_cast<scene::MeshSceneNode*>(node)->getMesh()->getTextureCoord());
			ImGui::Text("NormalCoord	 : %d", static_cast<scene::MeshSceneNode*>(node)->getMesh()->getNormalCoord());
		}
	
		if ((node != (node->getScene()->getRootNode())) &&
			(node != ((scene::SceneNode*)(node->getScene()->getActiveCamera()))) &&
			ImGui::SmallButton("Delete"))
			{
				if (_edit_material_window->getActiveNode() == node)
				{
					_edit_material_window->setVisible(false);
					_edit_material_window->setActiveNode(nullptr);
				}
				node->addToDeletionQueue();
				ImGui::TreePop();
				return;
			}
		
			if ((node != (node->getScene()->getRootNode())) &&
			(node != ((scene::SceneNode*)(node->getScene()->getActiveCamera()))) &&			
			ImGui::SmallButton("Show Collider"))
			{
				ImGui::Text("text");
				std::cout << "WIP" << std::endl;
			}

			if ((node != (node->getScene()->getRootNode())) &&
			(node != ((scene::SceneNode*)(node->getScene()->getActiveCamera()))) &&
			ImGui::SmallButton("Save"))
			{
				ImGui::OpenPopup("Save");
				ImGui::TreePop();
				return;
			}
			if (ImGui::BeginPopup("Save"))
			{
				ImGui::Text("Save done");
				ImGui::EndPopup();
			}

		if ((node != (node->getScene()->getRootNode())) &&
			(node != ((scene::SceneNode*)(node->getScene()->getActiveCamera()))) &&
			ImGui::SmallButton("Edit Material"))
			{
				_edit_material_window->setVisible(true);
				_edit_material_window->setActiveNode(node);
				ImGui::TreePop();
				return;
			}

		for (scene::SceneNode* child : node->getChildrens())
		{
			DebugWindow::DisplayNodesTree(child);
		}
		ImGui::TreePop();
	}
}

} // namespace id
