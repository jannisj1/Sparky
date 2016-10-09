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
			COLOR,
			FLOW_DIRECTION
		};

	private:
		ValueType m_ValueType;

	public:
		CSSValue(ValueType vt)
			: m_ValueType(vt) { }
		virtual ~CSSValue() {}
	};

	class CSSColor : public CSSValue
	{
		union
		{
			uint32 m_Color;
			struct {
				byte r, g, b, a;
			};
		};
		
	public:
		CSSColor()
			: CSSValue(ValueType::COLOR)
		{
			m_Color = 0xFFFFFFFF;
		}

		CSSColor(byte r, byte g, byte b, float a = 1.0f)
			: CSSValue(ValueType::COLOR), r(r), g(g), b(b), a((byte)(a*255.0f)) {}

		inline uint32 GetColor() const { return m_Color; }
	};

	class CSSLength : public CSSValue
	{
	public:
		enum LengthUnit
		{
			PIXEL,
			PERCENT,
			EM,
			AUTO
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

		inline bool IsAuto() const { return m_Lu == AUTO; }

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

			case AUTO:
				SP_ASSERT(false, "Auto not convertable to pixel sryy");
				return 0.0f;
				break;

			default:
				return 0.0f;
				break;
			}
		}
	};

	class CSSFlowDirection : public CSSValue
	{
	public:
		enum FlowDirection
		{
			DOWN,
			UP,
			LEFT,
			RIGHT
		};

	private:
		FlowDirection m_Fd;
		bool m_Wrap;

	public:
		CSSFlowDirection(FlowDirection fd, bool wrap = false)
			: m_Fd(fd), CSSValue(CSSValue::ValueType::FLOW_DIRECTION) {}

		inline FlowDirection GetDirection() const { return m_Fd; }
		inline bool IsWrapping() const { return m_Wrap; }
	};

} }