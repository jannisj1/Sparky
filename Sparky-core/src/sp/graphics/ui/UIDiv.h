#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIDiv : public Widget
	{
	protected:
		

	public:
		UIDiv(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement, bool activatable = false, bool focusable = false);

		css::CSSBounds CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace) override;
		void OnRender(Renderer2D& renderer) override;

		void MoveBy(const maths::vec2& delta) override;

		/*
		virtual float GetWidth(const css::CSSBounds& space) override;
		virtual float GetHeight(const css::CSSBounds& space) override;
		*/
	};

} } }