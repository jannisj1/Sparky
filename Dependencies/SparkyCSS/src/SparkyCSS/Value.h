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
			FLOW_DIRECTION,
			BORDER_STYLE,
			JUSTIFY_CONTENT,
			POSITION,
			DISPLAY
		};

	private:
		ValueType m_ValueType;

	public:
		CSSValue(ValueType vt)
			: m_ValueType(vt) { }
		virtual ~CSSValue() {}

		ValueType GetType() const { return m_ValueType; }
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
			FIT_CHILDREN
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

		inline bool FitChildren() const { return m_Lu == FIT_CHILDREN; }

		float ToPixel(UIElementCSSInfo *cssinfo, bool horizontal)
		{
			switch (m_Lu)
			{
			case PIXEL:
				return m_Val;
				
			case PERCENT:
				if (horizontal)
					return cssinfo->InnerBounds.width * m_Val;
				else
					return cssinfo->InnerBounds.height * m_Val;
				break;

			case EM:
				return m_Val * 16.0f;
				
			case FIT_CHILDREN:
				SP_ASSERT(false, "fit-children not convertable to pixel sryy");
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
			RIGHT,
			NOFLOW
		};

	private:
		FlowDirection m_Fd;
		bool m_Wrap;

	public:
		CSSFlowDirection(FlowDirection fd, bool wrap = false)
			: m_Fd(fd), m_Wrap(wrap), CSSValue(CSSValue::ValueType::FLOW_DIRECTION) {}

		inline FlowDirection GetDirection() const { return m_Fd; }
		inline bool IsWrapping() const { return m_Wrap; }
	};

	class CSSBorderStyle : public CSSValue
	{
	public:
		enum BorderStyle
		{
			SOLID,
			NONE
		};

	private:
		BorderStyle m_Bs;

	public:
		CSSBorderStyle(BorderStyle bs)
			: m_Bs(bs), CSSValue(CSSValue::ValueType::BORDER_STYLE) {}

		inline BorderStyle GetBorderStyle() const { return m_Bs; }
	};

	class CSSContentJustification : public CSSValue
	{
	public:
		enum ContentJustification
		{
			START,
			END,
			CENTER,
			SPACE_BETWEEN,
			SPACE_AROUND
		};

	private:
		ContentJustification m_JC;

	public:
		CSSContentJustification(ContentJustification jc)
			: m_JC(jc), CSSValue(CSSValue::ValueType::JUSTIFY_CONTENT) {}

		inline ContentJustification Get() const { return m_JC; }
	};

	class CSSPosition : public CSSValue
	{
	public:
		enum Position
		{
			STATIC,
			RELATIVE,
			ABSOLUTE,
			FIXED
		};

	private:
		Position m_Pos;

	public:
		CSSPosition(Position pos)
			: m_Pos(pos), CSSValue(CSSValue::ValueType::POSITION) {}

		inline Position Get() const { return m_Pos; }
	};

	class CSSDisplay : public CSSValue
	{
	public:
		enum Display
		{
			NONE,
			AUTO
		};

	private:
		Display m_Dis;

	public:
		CSSDisplay(Display dis)
			: m_Dis(dis), CSSValue(CSSValue::ValueType::DISPLAY) { }

		Display Get() const { return m_Dis; }
	};

} }