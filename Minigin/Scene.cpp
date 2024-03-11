#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

#include "imgui.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

void Scene::DisplayHierarchy()
{
	if (ImGui::Begin("Hierarchy"))
	{
		for (size_t i{}; i < m_objects.size(); ++i)
		{
			DisplayGameObject(m_objects[i].get(), (int)i);
		}
		ImGui::End();
	}
}

void Scene::DisplayGameObject(const GameObject* obj, int i)
{
	ImGuiTreeNodeFlags parentFlags =
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth;

	ImGuiTreeNodeFlags childFlags =
		ImGuiTreeNodeFlags_OpenOnArrow |
		ImGuiTreeNodeFlags_OpenOnDoubleClick |
		ImGuiTreeNodeFlags_SpanAvailWidth |
		ImGuiTreeNodeFlags_Leaf;
	bool hasChildren = !obj->m_children.empty();
	const auto flagsToUse = hasChildren ? parentFlags: childFlags;
	if (ImGui::TreeNodeEx(( std::to_string(i) + " " + obj->GetName()).c_str(), flagsToUse))
	{
		if(hasChildren)
		{
			for(size_t j{}; j < obj->m_children.size(); ++j)
			{
				DisplayGameObject(obj->m_children[j].get(), static_cast<int>(j));
			}
		}
		ImGui::TreePop();
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
