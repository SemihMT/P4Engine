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
		Texture(const std::shared_ptr<GameObject>& owner);
		~Texture() override = default;

		explicit Texture(const std::shared_ptr<GameObject>& owner, const std::string& fileName);

		Texture(const Texture& other) = delete;
		Texture(Texture&& other) = delete;
		Texture& operator=(const Texture& other) = delete;
		Texture& operator=(Texture&& other) = delete;

	public:
		void Render() const override;

	public:
		void SetTexture(const std::string& fileName);

	private:
		std::shared_ptr<Texture2D> m_texture{};
	};

}
