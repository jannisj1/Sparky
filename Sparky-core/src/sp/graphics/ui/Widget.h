#pragma once
#include "sp/sp.h"

#include "sp/maths/maths.h"
#include "sp/css/CSSManager.h"
#include "sp/graphics/Renderable2D.h"

#include <SparkyCSS/SparkyCSS.h>

namespace sp { namespace graphics { namespace ui {

	class SP_API Widget
	{
	public:
		enum WidgetState
		{
			ACTIVE,
			HOVER,
		};
	protected:
		WidgetState m_State;
		maths::Rectangle m_Bounds;
		
		css::UIElementCSSInfo m_CSSInfo;
		css::CSSManager* m_CSSManager;

	public:
		Widget(css::UIElementCSSInfo cssInfo, css::CSSManager* cssManager)
			: m_CSSInfo(cssInfo), m_CSSManager(cssManager) { }
		
	public:
		virtual bool OnMousePressed(events::MousePressedEvent& e);
		virtual bool OnMouseReleased(events::MouseReleasedEvent& e);
		virtual bool OnMouseMoved(events::MouseMovedEvent& e);

		virtual void OnUpdate();
		virtual void OnRender(Renderer2D& renderer);

		inline const maths::Rectangle& GetBounds() const { return m_Bounds; }
		inline maths::Rectangle& GetBounds() { return m_Bounds; }
		inline void SetBounds(const maths::Rectangle& bounds) { m_Bounds = bounds; }
		
		inline const css::UIElementCSSInfo &GetCSSInfo() const { return m_CSSInfo; }
	};

} } }