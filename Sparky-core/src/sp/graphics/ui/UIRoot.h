#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UIRoot : public Widget
	{
	protected:
		

	public:
		UIRoot(css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		virtual void OnUpdate(const maths::Rectangle& space) override;
		virtual void OnRender(Renderer2D& renderer) override;


	};

} } }