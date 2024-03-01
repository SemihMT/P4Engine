#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}

Scene::~Scene() = default;

void Scene::Add(std::unique_ptr<GameObject> object)
{
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

void Scene::LateUpdate()
{
    for (auto& object : m_objects)
    {
        if (!object->IsDisabled())
            object->LateUpdate();
    }
}
