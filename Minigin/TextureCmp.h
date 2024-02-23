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
		~Texture() override = default;

		explicit Texture(const std::string& fileName)
		{
			SetTexture(fileName);
		};

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
			const auto owner = GetOwner();
			const auto transform = owner->GetComponent<Transform>();
			const auto pos = transform->GetPosition();
			Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
		};
	public:
		void SetTexture(const std::string& fileName)
		{
			m_texture = ResourceManager::GetInstance().LoadTexture(fileName);
		};
	private:
		std::shared_ptr<Texture2D> m_texture{};
	};
}