#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "UIDiv.h"

namespace sp { namespace graphics { namespace ui {

	class UIRoot : public UIDiv
	{
	public:
		UIRoot(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		virtual float GetHeight(const css::CSSBounds& space) override;
	};

} } }