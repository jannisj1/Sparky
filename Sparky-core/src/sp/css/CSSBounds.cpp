#include <sp/sp.h>
#include "CSSBounds.h"
#include "sp/app/Application.h"

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

	maths::Rectangle CSSBounds::ToRectangle()
	{
		maths::Rectangle res;

		res.width = width / 2;
		res.height = height / 2;
		res.x = x + width / 2;
		res.y = y + height / 2;

		res.y = Application::GetApplication().GetWindowHeight() - res.y;

		return res;
	}

} }