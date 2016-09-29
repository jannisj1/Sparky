#include "sp/sp.h"
#include "UIRoot.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UIRoot::UIRoot(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(cssManager, domElement)
	{

	}

	void UIRoot::OnUpdate(const css::CSSBounds& space)
	{
		m_Bounds = space;

		float xOffset = 0.0f, yOffset = 0.0f;

		for (auto c : m_Children)
		{
			float height = c->GetHeight();
			float width = c->GetWidth();

			c->OnUpdate(css::CSSBounds(space.x + xOffset, space.y + yOffset, space.x + width, space.y + height));
			yOffset += height;
		}
	}

	void UIRoot::OnRender(Renderer2D& renderer)
	{
		for (auto c : m_Children)
		{
			c->OnRender(renderer);
		}
	}

} } }