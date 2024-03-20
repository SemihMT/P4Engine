#include "Scene.h"
#include "GameObject.h"

#include <algorithm>

#include "imgui.h"
#include "imgui_internal.h"

using namespace dae;

unsigned int Scene::m_idCounter = 0;

Scene::Scene(const std::string& name) : m_name(name) {}


//This needs some hardcore refactoring.... but it works :D
void Scene::DisplayHierarchy()
{

    ImGui::Begin("Hierarchy"); 

    //Making the whole hierarchy window a drop target to un-parent parented objects
    //from: https://github.com/ocornut/imgui/issues/5539
    const ImRect innerRect = ImGui::GetCurrentWindow()->InnerRect;
	GameObject* draggedObj{ nullptr };
    if (ImGui::BeginDragDropTargetCustom(innerRect, ImGui::GetID("Hierarchy")))
    {
        if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT", ImGuiDragDropFlags_AcceptBeforeDelivery | ImGuiDragDropFlags_AcceptNoDrawDefaultRect))
        {
            if (payload && payload->Data)
            {

                if (payload->IsPreview())
                {
                    ImGui::GetForegroundDrawList()->AddRectFilled(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget, 0.05f));
                    ImGui::GetForegroundDrawList()->AddRect(innerRect.Min, innerRect.Max, ImGui::GetColorU32(ImGuiCol_DragDropTarget), 0.0f, 0, 2.0f);
                }

                if (payload->IsDelivery())
                {
                    draggedObj = *(GameObject**)payload->Data;
                    draggedObj->SetParent(nullptr, true);
                }
            }
        }
        ImGui::EndDragDropTarget();
    }



    //Display the objects
    for (const auto& object : m_objects)
    {
        if(!object) continue;
        if (DisplayGameObject(object.get(),draggedObj)) {
            // If an object is selected, update the selected object
            m_selectedObject = object.get();
        }
        //DragGameObject(object.get());
    }
   
    ImGui::End();

    // Display the object information window
    if (m_selectedObject != nullptr) {
        DisplayObjectInfo(m_selectedObject);
    }
}

bool Scene::DisplayGameObject(GameObject* obj, GameObject* draggedObj)
{
    ImGuiTreeNodeFlags treeNodeFlags =
        ImGuiTreeNodeFlags_OpenOnArrow |
        ImGuiTreeNodeFlags_OpenOnDoubleClick |
        ImGuiTreeNodeFlags_SpanAvailWidth;


    bool isDraggingThisObj = (draggedObj == obj);
    if (isDraggingThisObj)
        ImGui::PushStyleColor(ImGuiCol_Header, ImVec4(0.5f, 0.5f, 0.5f, 1.0f));



    bool isRootObj = obj->m_children.empty();
    if (isRootObj)
        treeNodeFlags |= ImGuiTreeNodeFlags_Leaf;

    bool isNodeOpen = ImGui::TreeNodeEx(obj->GetName().c_str(), treeNodeFlags);

    if (isNodeOpen)
    {
        // If the object is being dragged and dropped onto, set its parent
        if (ImGui::BeginDragDropTarget())
        {
            if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("GAMEOBJECT"))
            {
                if (payload && payload->Data)
                {
                    GameObject* droppedObj = *(GameObject**)payload->Data;
                    // Set the parent of the dragged object to this object
                    droppedObj->SetParent(obj, true);
                }
            }
            ImGui::EndDragDropTarget();
        }
        DragGameObject(obj);
        // Display children recursively
        for (const auto& child : obj->m_children)
        {
            DisplayGameObject(child.get(), draggedObj);
        }
        ImGui::TreePop();
    }
    if (isDraggingThisObj)
    {
        ImGui::PopStyleColor();
    }
    // Return true if the object is selected
    return isNodeOpen && ImGui::IsItemClicked();
}

void Scene::DisplayChildren(const GameObject* obj, GameObject* draggedObj)
{
    for (const auto& child : obj->m_children)
    {
        if (!child)
            continue;

        if (DisplayGameObject(child.get(), draggedObj))
        {
            // If an object is selected, update the selected object
            m_selectedObject = child.get();
        }

        // Recursive call to handle children of the current child object
        DisplayChildren(child.get(), draggedObj);
    }
}

void Scene::DragGameObject(GameObject* obj)
{
    if (obj != nullptr)
    {
        // Start drag and drop operation
        if (ImGui::BeginDragDropSource())
        {
            // Set payload with the object pointer
            ImGui::SetDragDropPayload("GAMEOBJECT", &obj, sizeof(GameObject*));

            // Display object name as drag preview
            ImGui::Text(obj->GetName().c_str());

            ImGui::EndDragDropSource();
        }
    }
}

void Scene::DisplayObjectInfo(const GameObject* obj)
{
    // Begin the object information window
    ImGui::Begin("Object Info",nullptr,ImGuiWindowFlags_NoFocusOnAppearing);

    // Display object information
    ImGui::TextWrapped("Name: %s", obj->GetName().c_str());
    ImGui::Separator();
    ImGui::TextWrapped("pos: %.1f, %.1f, %.1f", obj->GetTransform()->GetLocalPosition().x, obj->GetTransform()->GetLocalPosition().y, obj->GetTransform()->GetLocalPosition().z);

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

GameObject* Scene::Pop(GameObject* object)
{
    //Find the given GO in the list
    const auto it = std::ranges::find_if(m_objects,
        [&](const std::unique_ptr<GameObject>& ptr) {return ptr.get() == object; });

    //If found
    if (it != m_objects.end())
    {
        //store the found object's raw ptr
        auto tmp = it->get();

        //Release the unique pointer from its cleanup/management duties
        //(to prevent the destructor from being called when we remove it from the owning vector)
        it->release();
        //Remove the released unique pointer from the vector
        //Which would be a unique pointer to nullptr 
       m_objects.erase(it);
       return tmp;
    }
    return nullptr;
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
