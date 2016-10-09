#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIEmpty : public Widget
	{
	public:
		UIEmpty(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		void OnUpdate(const css::CSSBounds& space) override;
		void OnRender(Renderer2D& renderer) override;
		float GetWidth(const css::CSSBounds& space) override;
		float GetHeight(const css::CSSBounds& space) override;
	};

} } }