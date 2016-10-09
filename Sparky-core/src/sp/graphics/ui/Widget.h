#pragma once
#include "sp/sp.h"

#include "sp/maths/maths.h"
#include "sp/css/CSSManager.h"
#include "sp/graphics/Renderable2D.h"
#include "sp/css/CSSBounds.h"

#include <SparkyCSS/SparkyCSS.h>
#include <tinyxml2.h>

namespace sp { namespace graphics { namespace ui {

	class SP_API Widget
	{
	protected:
		css::CSSBounds m_Bounds;
		css::UIElementCSSInfo m_CSSInfo;
		css::CSSManager *m_CSSManager;
		tinyxml2::XMLElement *m_DOMElement;
		std::vector<Widget*> m_Children;
		bool m_Activatable, m_Focusable;
		bool m_IsDivContainer;

	public:
		Widget(Widget *parent, css::CSSManager *cssManager, tinyxml2::XMLElement *domElement, bool activatable = false, bool focusable = false);

	public:
		static ui::Widget *FocusedWidget;
		virtual bool OnMousePressed(events::MousePressedEvent& e);
		virtual bool OnMouseReleased(events::MouseReleasedEvent& e);
		virtual bool OnMouseMoved(events::MouseMovedEvent& e);

		virtual void OnUpdate(const css::CSSBounds& space) = 0;
		virtual void OnRender(Renderer2D& renderer);

		virtual float GetWidth(const css::CSSBounds& space) = 0;
		virtual float GetHeight(const css::CSSBounds& space) = 0;

		inline css::UIElementCSSInfo &GetCSSInfo() { return m_CSSInfo; }
		inline const css::CSSValue *GetCSSValue(css::CSSKey key) { return m_CSSManager->GetValue(m_CSSInfo, key); }
		
		inline void AddChild(ui::Widget *child) { m_Children.push_back(child); }
		inline std::vector<ui::Widget*>& GetChildren() { return m_Children; }

	protected:
		template<class T>
		inline T *Get(css::CSSKey key) { return m_CSSManager->Get<T>(m_CSSInfo, key); }
	};

} } }