#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "UIDiv.h"

namespace sp { namespace graphics { namespace ui {
	
	class UIButton : public UIDiv
	{
	public:
		UIButton(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);
	};
	
} } }