#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIEmpty : public Widget
	{
	public:
		UIEmpty(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		virtual void OnUpdate(const css::CSSBounds& space) override;
		virtual void OnRender(Renderer2D& renderer) override;

		float GetWidth() override;
		float GetHeight() override;
	};
} } }