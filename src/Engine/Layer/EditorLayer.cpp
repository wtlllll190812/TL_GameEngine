#include "EditorLayer.h"
#include "imgui.h"
#include "GuiWindow.h"
#include "Application.h"
#include "Scene.h"
#include "GameObject.h"
#include "Debug.h"
#include "FrameBuffer.h"
#include "Component.h"
#include "Camera.h"
#include <string>
using namespace std;

#include "Reflection.h"
#include "Transform.h"
#include "Input.h"
#include "GLFW/glfw3.h"
#include "ImGuizmo.h"
#include <glm/gtc/type_ptr.hpp>
#include "Transform.h"

EditorLayer::EditorLayer(std::shared_ptr<Scene> s)
{
	currentScene = s;
	editorCamera = shared_ptr<GameObject>(new GameObject());
	editorCamera->AddComponent(new Camera());
	Transform* tr = s->camera->gameobject->transform;
	editorCamera->transform->position = tr->position;
	editorCamera->transform->rotation = tr->rotation;

	auto Docking = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			bool p_open = true;
			static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None | ImGuiDockNodeFlags_PassthruCentralNode;

			ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar;

			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
			window_flags |= ImGuiWindowFlags_NoBackground;

			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
			ImGui::Begin("DockSpace Demo", &p_open, window_flags);
			ImGui::PopStyleVar();

			ImGui::PopStyleVar(2);

			// Submit the DockSpace
			ImGuiIO& io = ImGui::GetIO();
			if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
			{
				ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
				ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
			}
			ImGui::End(); },
		"DockSpace"));
	RegisterGuiWindow(Docking);

	auto Editor = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			if (ImGui::BeginMainMenuBar())
			{
				if (ImGui::BeginMenu("File"))
				{
					ImGui::EndMenu();
				}
				if (ImGui::BeginMenu("Edit"))
				{
					if (ImGui::MenuItem("Save")) {
						currentScene->Save();
						Debug::GetEngineLogger()->info("Save Current Scene");
					}
					if (ImGui::MenuItem("Empty GameObject")) {
						currentScene->AddGameObject(shared_ptr<GameObject>(new GameObject()));
						Debug::GetEngineLogger()->info("Add Empty GameObject");
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			} },
		"Editor"));
	RegisterGuiWindow(Editor);

	auto Hierarchy = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			static bool hierarchy = true;
			if (hierarchy)
			{
				ImGui::Begin("Hierarchy", &hierarchy);
				if (currentScene != nullptr)
				{
					if (ImGui::CollapsingHeader("Window options"))
					{
						for (auto i : currentScene->gameobjects)
						{
							if (ImGui::Button(i->name.c_str())) 
							{
								currentObj = i;
							}
						}
					}
				}
				ImGui::End();
			} },
		"Hierarchy"));
	RegisterGuiWindow(Hierarchy);

	auto Inspector = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			static bool Inspector = true;
			if (Inspector)
			{
				ImGui::Begin("Inspector", &Inspector);
				if (currentObj != nullptr)
				{
					//show Components
					for (auto i : currentObj->components)
					{
						if (ImGui::CollapsingHeader(i->GetName().c_str()))
						{
							i->GuiDisPlay();
						}
					}
					static bool listOpen = false;

					//add component button
					if (listOpen||ImGui::Button("Add Component", ImVec2(160, 30)))
					{
						listOpen = true;
						auto start = ReflectionManager::instance().GetMemberByTag(ReflectionTag::Component);
						int count= ReflectionManager::instance().GetMemberCountByTag(ReflectionTag::Component);
						for (int k = 0; k != count; k++, start++)
						{
							if (ImGui::Button(start->second.c_str(), ImVec2(140, 20)))
							{
								currentObj->AddComponent((Component*)ReflectionManager::instance().getClassByName(start->second));
								listOpen = false;
							}
						}
					}
				}
				
				
				ImGui::End();
			} },
		"Inspector"));
	RegisterGuiWindow(Inspector);

	auto Console = shared_ptr<GuiWindow>(new GuiWindow([]()
		{
			static bool Console = true;
			static vector<string> logBuffer;
			if (Console)
			{
				ImGui::Begin("Console", &Console);
				string str;
				while (std::getline(Debug::appLogOss, str))
				{
					logBuffer.push_back(str);
				}

				for (auto& s : logBuffer)
				{
					ImGui::BulletText(s.c_str());
				}

				ImGui::End();
			} },
		"Console"));
	RegisterGuiWindow(Console);

	auto SceneView = shared_ptr<GuiWindow>(new GuiWindow([this]()
		{
			ImGui::Begin("Scene");
			{
				//?????????????????????
				auto viewportMinRegion = ImGui::GetWindowContentRegionMin();
				auto viewportMaxRegion = ImGui::GetWindowContentRegionMax();
				auto viewportOffset = ImGui::GetWindowPos();
				glm::vec2 m_ViewportBounds0 = { viewportMinRegion.x + viewportOffset.x, viewportMinRegion.y + viewportOffset.y };
				glm::vec2 m_ViewportBounds1 = { viewportMaxRegion.x + viewportOffset.x, viewportMaxRegion.y + viewportOffset.y };
				ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();

				//????????????????????????
				/*auto fb = Application::instance().mWindows->GetFrameBuffer();
				ImGui::Image((ImTextureID)fb->GetFBO(), viewportPanelSize, ImVec2(0, 1), ImVec2(1, 0));
				fb->Resize(viewportPanelSize.x, viewportPanelSize.y);*/

				//??????gizmos
				if (currentObj)
				{
					ImGuizmo::SetOrthographic(false);
					ImGuizmo::SetDrawlist();

					//??????gizmos??????
					ImGuizmo::SetRect(m_ViewportBounds0.x, m_ViewportBounds0.y, m_ViewportBounds1.x - m_ViewportBounds0.x, m_ViewportBounds1.y - m_ViewportBounds0.y);


					const glm::mat4& cameraProjection = GetEditorCamera()->GetProjMatrix();
					glm::mat4 cameraView = GetEditorCamera()->GetViewMatrix();
					glm::mat4 model = currentObj->transform->GetModelMatrix();



					bool snap = Input::GetKeyDown(341);
					float snapValue = 0.5f; // Snap to 0.5m for translation/scale
					static int m_GizmoType = ImGuizmo::OPERATION::TRANSLATE;
					if (m_GizmoType == ImGuizmo::OPERATION::ROTATE)
						snapValue = 45.0f;

					float snapValues[3] = { snapValue, snapValue, snapValue };

					ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
						(ImGuizmo::OPERATION)m_GizmoType, ImGuizmo::LOCAL, glm::value_ptr(model),
						nullptr, snap ? snapValues : nullptr);

					if (ImGuizmo::IsUsing())
					{
						glm::vec3 translation, rotation, scale;
						currentObj->transform->Decompose(model);

						/*glm::vec3 deltaRotation = rotation - currentObj->transform->rotation;
						currentObj->transform->position = translation;
						currentObj->transform->rotation += deltaRotation;
						currentObj->transform->scale = scale;*/
					}
				}
			}
			
			ImGui::End();
		},
		"SceneView"));
	RegisterGuiWindow(SceneView);
}

EditorLayer::~EditorLayer()
{
}

void EditorLayer::OnUpdate()
{
	RenderStart();


	static glm::vec2 lastPos = Input::MousePos();

	//ImGui::ShowDemoWindow();
	for (std::shared_ptr<GuiWindow> i : uiWindows)
	{
		i->Render();
	}

	if (Input::GetMouseButtonDown(GLFW_MOUSE_BUTTON_2))
	{
		lastPos = Input::MousePos();
	}
	if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_2))
	{
		glm::vec2 dir = Input::MousePos() - lastPos;
		editorCamera->transform->rotation.x -= dir.x/10;
		editorCamera->transform->rotation.z += dir.y/10;
		lastPos = Input::MousePos();
	}

	if (Input::GetMouseButton(GLFW_MOUSE_BUTTON_1))
	{
		//editorCamera->transform->rotation.z += 0.05f;
		//editorCamera->transform->Translate(editorCamera->transform->GetFront(), 0.05f);
	}
	RenderEnd();
}

void EditorLayer::SetScene(Scene* s)
{
}

Camera* EditorLayer::GetEditorCamera()
{
	return editorCamera->GetComponent<Camera>();
}

bool EditorLayer::OnMouseMovedEvent(MouseMovedEvent& e)
{
	return false;
}

bool EditorLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
{
	ImGuiIO& io = ImGui::GetIO();
	io.MouseWheelH += e.GetXOffset();
	io.MouseWheel += e.GetYOffset();

	editorCamera->transform->Translate(editorCamera->transform->GetFront(), e.GetYOffset());

	return false;
}
