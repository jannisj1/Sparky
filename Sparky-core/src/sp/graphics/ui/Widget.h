#pragma once
#include "sp/sp.h"

#include "sp/maths/maths.h"
#include "sp/css/CSSManager.h"
#include "sp/graphics/Renderable2D.h"

#include <SparkyCSS/SparkyCSS.h>
#include <tinyxml2.h>

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
		css::CSSManager *m_CSSManager;
		tinyxml2::XMLElement *m_DOMElement;
		std::vector<Widget*> m_Children;

	public:
		Widget(css::CSSManager *cssManager, tinyxml2::XMLElement *domElement);

	public:
		virtual bool OnMousePressed(events::MousePressedEvent& e);
		virtual bool OnMouseReleased(events::MouseReleasedEvent& e);
		virtual bool OnMouseMoved(events::MouseMovedEvent& e);

		virtual void OnUpdate(const maths::Rectangle& space);
		virtual void OnRender(Renderer2D& renderer);

		virtual float GetWidth() { return 0.0f; }
		virtual float GetHeight() { return 0.0f; }

		inline const css::UIElementCSSInfo &GetCSSInfo() const { return m_CSSInfo; }
		inline const css::CSSValue *GetCSSValue(css::CSSKey key) { return m_CSSManager->GetValue(m_CSSInfo, key); }
		
		inline void AddChild(ui::Widget *child) { m_Children.push_back(child); }
		inline std::vector<ui::Widget*>& GetChildren() { return m_Children; }
	};

} } }