#include "Text.h"
#include <stdexcept>
#include <SDL_ttf.h>
#include "Renderer.h"
#include "Font.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Texture2D.h"
#include "Transform.h"
using namespace dae;
std::string Text::s_defaultFont = "Lingua.otf";
Text::Text(GameObject* owner, std::shared_ptr<Font> font, const std::string& text)
	: BaseComponent(owner),
	m_needsUpdate(true),
	m_text{ text },
	m_font{ std::move(font) }
{
}

Text::Text(GameObject* owner, std::shared_ptr<Font> font)
	:BaseComponent(owner),
	m_needsUpdate(true),
	m_text{},
	m_font(std::move(font))
{
}

Text::Text(GameObject* owner, const std::string& text)
	:BaseComponent(owner),
	m_needsUpdate(true),
	m_text(text),
	m_font(ResourceManager::GetInstance().LoadFont(s_defaultFont, 36))

{
}

void Text::Update()
{
	if (m_needsUpdate)
	{
		constexpr SDL_Color color = { 255,255,255,255 }; // only white text is supported now
		const auto surf = TTF_RenderText_Blended(m_font->GetFont(), m_text.c_str(), color);
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);
		m_textTexture = std::make_shared<Texture2D>(texture);
		m_needsUpdate = false;
	}
}

void Text::Render() const
{
	if (m_textTexture != nullptr)
	{
		const auto& pos = GetOwner()->GetComponent<Transform>()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_textTexture, pos.x, pos.y);
	}
}

void Text::SetText(const std::string& text)
{
	m_text = text;
	m_needsUpdate = true;
}
