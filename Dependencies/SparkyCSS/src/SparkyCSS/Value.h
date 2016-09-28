#pragma once
#include <sp/sp.h>
#include <sp/app/Application.h>

namespace sp { namespace css {

	class CSSValue
	{
	public:
		enum class ValueType
		{
			LENGTH,
			COLOR
		};

	private:
		ValueType m_ValueType;

	public:
		CSSValue(ValueType vt)
			: m_ValueType(vt) { }
	};

	class CSSColor : public CSSValue
	{
		uint32 m_Color;

	public:
		CSSColor()
			: CSSValue(ValueType::COLOR)
		{
			m_Color = 0xFFFFFFFF;
		}

		CSSColor(byte r, byte g, byte b, byte a)
			: CSSValue(ValueType::COLOR)
		{
			m_Color = ((byte)(a == 1 ? 255 : 0) << 24) + (b << 16) + (g << 8) + r;
		}

		inline uint32 GetColor() const { return m_Color; }
	};

	class CSSLength : public CSSValue
	{
	public:
		enum LengthUnit
		{
			PIXEL,
			PERCENT,
			EM
		};

	private:
		float m_Val;
		LengthUnit m_Lu;

	public:
		CSSLength(float val, LengthUnit lu)
			: m_Val(val), m_Lu(lu), CSSValue(CSSValue::ValueType::LENGTH)
		{
			if (lu == PERCENT)
				m_Val /= 100.0f;
		}

		float ToPixel(bool horizontal)
		{
			switch (m_Lu)
			{
			case PIXEL:
				return m_Val;
				break;

			case PERCENT:
				if (horizontal)
					return Window::GetWindowClass(nullptr)->GetWidth() * m_Val;
				else
					return Window::GetWindowClass(nullptr)->GetHeight() * m_Val;
				break;

			case EM:
				return m_Val * 16.0f;
				break;

			default:
				return 0.0f;
				break;
			}
		}
	};

} }