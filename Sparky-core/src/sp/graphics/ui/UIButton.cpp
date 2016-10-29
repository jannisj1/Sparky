#include "sp/sp.h"
#include "UIButton.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;
	using namespace css;
	
	UIButton::UIButton(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: UIDiv(parent, cssManager, domElement, true)
	{
		
	}
	
} } }