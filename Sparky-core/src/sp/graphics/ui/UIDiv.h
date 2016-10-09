#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIDiv : public Widget
	{
	protected:
		

	public:
		UIDiv(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		void OnUpdate(const css::CSSBounds& space) override;
		void OnRender(Renderer2D& renderer) override;

		virtual float GetWidth() override;
		virtual float GetHeight() override;
	};

} } }