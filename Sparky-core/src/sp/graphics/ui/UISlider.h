#pragma once
#include "sp/sp.h"
#include "sp/String.h"

#include "Widget.h"

namespace sp { namespace graphics { namespace ui {

	class UISlider : public Widget
	{
	protected:
		bool m_Vertical;
		float m_Value;
		float m_MaxValue;
		float m_MinValue;
		float m_StepSize;
		float m_Factor;

	public:
		UISlider(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement);

		css::CSSBounds CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace);

		void OnRender(Renderer2D& renderer) override;
		bool OnMousePressed(events::MousePressedEvent& e) override;
		bool OnMouseReleased(events::MouseReleasedEvent& e) override;
		bool OnMouseMoved(events::MouseMovedEvent& e) override;
	};

} } }