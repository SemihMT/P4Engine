#pragma once
#include "GameObject.h"
#include <string>
#include "Texture2D.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "Transform.h"
namespace dae
{
	class Texture final : public BaseComponent
	{
	public:
		Texture() = default;
		virtual ~Texture() = default;

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) = delete;

	public:
		void Update() override 
		{
		};
		void Render() const override 
		{
			auto owner = GetOwner();
			auto transform = owner->GetComponent<Transform>();
			auto pos = transform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		};
	public:
		void SetTexture(const std::string& fileName)
		{
			m_Texture = ResourceManager::GetInstance().LoadTexture(fileName);
		};
	private:
		std::shared_ptr<Texture2D> m_Texture{};
	};
}