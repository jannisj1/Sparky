#pragma once
#include <sp/sp.h>
#include "sp/maths/maths.h"

namespace sp { namespace css {

	/// Note that CSSBounds is different to maths::Rectangle in that it treats position
	/// as top left and not in center
	class CSSBounds
	{
	public:
		union
		{
			maths::vec2 position;
			struct
			{
				float x;
				float y;
			};
		};
		union
		{
			maths::vec2 size;
			struct
			{
				float width;
				float height;
			};
		};

		CSSBounds();
		CSSBounds(float x, float y, float width, float height);

		bool Contains(const maths::vec2& point);

	};
	
} }