#pragma once
#include "SparkyCSS.h"

namespace sp { namespace css {
	
	enum LengthUnit
	{
		PIXEL,
		PERCENT
	};

	class CSSValue
	{
	public:
		enum ValueType
		{
			LENGTH
		};

	private:
		ValueType m_ValueType;

	public:
		CSSValue(ValueType vt)
			: m_ValueType(vt) { }

		virtual String ToString() = 0;

	};

	class CSSLength : public CSSValue
	{
		float m_Val;
		LengthUnit m_Lu;

	public:
		CSSLength(float val, LengthUnit lu)
			: m_Val(val), m_Lu(lu), CSSValue(CSSValue::LENGTH) { }

		String ToString() override
		{
			return std::to_string(m_Val);
		}
	};


} }