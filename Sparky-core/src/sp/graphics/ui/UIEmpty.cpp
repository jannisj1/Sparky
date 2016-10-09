#include <sp/sp.h>
#include "UIEmpty.h"

namespace sp { namespace graphics { namespace ui {
	
	UIEmpty::UIEmpty(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement) { }

	void UIEmpty::OnUpdate(const css::CSSBounds&) {}
	void UIEmpty::OnRender(Renderer2D& renderer) {}
	float UIEmpty::GetWidth(const css::CSSBounds& space) { return 0.0f; }
	float UIEmpty::GetHeight(const css::CSSBounds& space) { return 0.0f; }

} } }