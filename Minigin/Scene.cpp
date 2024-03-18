#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

#include "imgui.h"
#include "imgui_internal.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void Scene::DisplayHierarchy()
{
    ImGui::Begin("Hierarchy");
    for (const auto& object : m_objects)
    {
        if (DisplayGameObject(object.get())) {
            // If an object is selected, update the selected object
            m_selectedObject = object.get();
        }
    }
    ImGui::End();

    // Display the object information window
    if (m_selectedObject != nullptr) {
        DisplayObjectInfo(m_selectedObject);
    }
}

bool Scene::DisplayGameObject(const GameObject* obj)
{
    ImGuiTreeNodeFlags treeNodeFlags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;

    bool isRootObj = obj->m_children.empty();
    if (isRootObj)
        treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

    bool isNodeOpen = ImGui::TreeNodeEx(obj->GetName().c_str(), treeNodeFlags);

    if (isNodeOpen)
    {
        DisplayChildren(obj);
        ImGui::TreePop();
    }

    // Return true if the object is selected
    return isNodeOpen && ImGui::IsItemClicked();
}

void Scene::DisplayChildren(const GameObject* obj)
{
    for (const auto& child : obj->m_children)
    {
        DisplayGameObject(child.get());
    }
}

void Scene::DisplayObjectInfo(const GameObject* obj)
{
    // Begin the object information window
    ImGui::Begin("Object Info");

    // Display object information
    ImGui::Text("Name: %s", obj->GetName().c_str());
    ImGui::Separator();
    ImGui::Text("pos: %.1f, %.1f, %.1f", obj->GetTransform()->GetLocalPosition().x, obj->GetTransform()->GetLocalPosition().y, obj->GetTransform()->GetLocalPosition().z);

    // Add more information here if needed

    ImGui::End();

    // Dock the object information window below the hierarchy window
    ImGuiDockNode* dockspaceNode = ImGui::DockBuilderGetNode(ImGui::GetID("DockSpace"));
    if (dockspaceNode != nullptr)
    {
        ImGui::DockBuilderDockWindow("Object Info", dockspaceNode->ID);
        ImGui::DockBuilderSetNodeSize(dockspaceNode->ID, ImVec2(-1, ImGui::GetFrameHeightWithSpacing() * 6));
    }
}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
	if (object->GetParent() != nullptr)
	{
		std::cout << "Object has parent, should not get added to the scene!\n";
		return;
	}
	m_objects.emplace_back(std::move(object));
}

void Scene::Remove(GameObject* object)
{
	std::erase_if(m_objects, [&](const auto& ptr) {
		return ptr.get() == object;
		});
}

void Scene::RemoveAll()
{
	m_objects.clear();
}

void Scene::Update()
{
	for (auto& object : m_objects)
	{
		if (!object->IsDead() && !object->IsDisabled())
			object->Update();
	}

	std::erase_if(m_objects, [](const auto& object) { return object->IsDead(); });
}

void Scene::Render() const
{
	for (const auto& object : m_objects)
	{
		if (!object->IsDisabled())
			object->Render();
	}
}

void Scene::RenderImGui()
{
	for (const auto& object : m_objects)
	{
		if (!object->IsDisabled())
			object->RenderImGui();
	}

	//Unity-like hierarchy of game objects ↓ (WIP)
	DisplayHierarchy();
	
}

void Scene::LateUpdate()
{
	for (auto& object : m_objects)
	{
		if (!object->IsDisabled())
			object->LateUpdate();
	}
}
