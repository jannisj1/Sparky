#include <sp/sp.h>

#include "UIRoot.h"

namespace sp { namespace graphics { namespace ui {

	UIRoot::UIRoot(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: UIDiv(parent, cssManager, domElement) {}

} } }