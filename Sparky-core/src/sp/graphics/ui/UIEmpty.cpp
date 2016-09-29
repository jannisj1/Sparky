#include <sp/sp.h>
#include "UIEmpty.h"

namespace sp { namespace graphics { namespace ui {
	
	UIEmpty::UIEmpty(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(cssManager, domElement) { }

	void UIEmpty::OnUpdate(const css::CSSBounds&) {}
	void UIEmpty::OnRender(Renderer2D& renderer) {}
	float UIEmpty::GetWidth() { return 0.0f; }
	float UIEmpty::GetHeight() { return 0.0f; }
		
} } }