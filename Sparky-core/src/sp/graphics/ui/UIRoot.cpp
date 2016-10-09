#include <sp/sp.h>

#include "UIRoot.h"

namespace sp { namespace graphics { namespace ui {

	UIRoot::UIRoot(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: UIDiv(parent, cssManager, domElement) {}

	float UIRoot::GetHeight(const css::CSSBounds& space)
	{
		if (Get<css::CSSLength>(css::HEIGHT)->IsAuto())
		{
			return space.height;
		}
		else
		{
			return UIDiv::GetHeight(space);
		}
	}

} } }