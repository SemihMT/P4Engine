#pragma once
#include "BaseComponent.h"
#include "Font.h"
#include "Texture2D.h"
namespace dae
{
	
	class Text : public BaseComponent
	{
		
	public:
		Text(GameObject* owner, std::shared_ptr<Font> font, const std::string& text);
		Text(GameObject* owner, std::shared_ptr<Font> font);
		Text(GameObject* owner, const std::string& text);
		~Text() override = default;

		Text(const Text& other) = delete;
		Text(Text&& other) = delete;
		Text& operator=(const Text& other) = delete;
		Text& operator=(Text&& other) = delete;

		void Update() override;
		void Render() const override;

		static std::string s_defaultFont;
		void SetText(const std::string& text);

	private: 
		bool m_needsUpdate;
		std::string m_text {};
		std::shared_ptr<Font> m_font;
		std::shared_ptr<Texture2D> m_textTexture;

		
	};

}

