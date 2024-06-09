#pragma once
#include <BaseComponent.h>
#include <string>

namespace dae
{
	class IdentifierComponent final : public BaseComponent
	{
	public:
		IdentifierComponent(GameObject* owner);
		virtual ~IdentifierComponent() override = default;

		IdentifierComponent(const IdentifierComponent& other) = delete;
		IdentifierComponent(IdentifierComponent&& other) = delete;
		IdentifierComponent& operator=(const IdentifierComponent& other) = delete;
		IdentifierComponent& operator=(IdentifierComponent&& other) = delete;

		void Update() override;
		//void Render() override;
		//void LateUpdate() override;
		//void RenderImgui() override;
		std::string GetIdentifier() {return m_identifier;}
	private:
		void WriteHighscore();
		int m_index{0};
		std::string	m_identifier{"ABC"};
	};
}
