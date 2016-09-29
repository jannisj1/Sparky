#include <sp/sp.h>
#include "CSSBounds.h"

namespace sp { namespace css {

	CSSBounds::CSSBounds() {}

	CSSBounds::CSSBounds(float _x, float _y, float _width, float _height)
		: x(_x), y(_y), width(_width), height(_height)
	{
	
	}

	bool CSSBounds::Contains(const maths::vec2& point)
	{
		return ((point.x >= x) && (point.x < (x + width))) &&
			((point.y >= y) && (point.y < (y + height)));
	}

} }