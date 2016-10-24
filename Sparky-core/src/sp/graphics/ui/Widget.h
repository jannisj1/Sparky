#pragma once
#include "sp/sp.h"

#include "sp/maths/maths.h"
#include "sp/css/CSSManager.h"
#include "sp/graphics/Renderable2D.h"
#include "sp/css/CSSBounds.h"
#include "sp/graphics/Renderer2D.h"

#include <SparkyCSS/SparkyCSS.h>
#include <SparkyJS/SparkyJS.h>
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
		css::CSSBounds &m_InnerBounds = m_CSSInfo.InnerBounds;
		css::CSSBounds m_OuterBounds;
		Widget *m_Parent;
		spjs::ExecutionEngine *m_JS = nullptr;

	public:
		Widget(Widget *parent, css::CSSManager *cssManager, tinyxml2::XMLElement *domElement, bool activatable = false, bool focusable = false);

	public:
		static ui::Widget *FocusedWidget;
		bool OnMousePressed(events::MousePressedEvent& e);
		bool OnMouseReleased(events::MouseReleasedEvent& e);
		bool OnMouseMoved(events::MouseMovedEvent& e);

		//void OnHover()

		virtual css::CSSBounds CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace) = 0;
		virtual void OnRender(Renderer2D& renderer);
		/*
		virtual float GetWidth(const css::CSSBounds& space) = 0;
		virtual float GetHeight(const css::CSSBounds& space) = 0;
		*/

		inline void SetEE(spjs::ExecutionEngine *ee) { m_JS = ee; }

		inline css::UIElementCSSInfo &GetCSSInfo() { return m_CSSInfo; }
		inline const css::CSSValue *GetCSSValue(css::CSSKey key) { return m_CSSManager->GetValue(m_CSSInfo, key); }
		
		inline void AddChild(ui::Widget *child) { m_Children.push_back(child); }
		inline std::vector<ui::Widget*>& GetChildren() { return m_Children; }

		inline const css::CSSBounds& GetOuterBounds() const { return m_OuterBounds; }

		virtual void MoveBy(const maths::vec2& delta);

		template<class T>
		inline T *Get(css::CSSKey key) { return m_CSSManager->Get<T>(m_CSSInfo, key); }
		
		maths::vec2 m_ChildrenWrapSize; // Should be protected
	
	protected:
		inline float GetPixelWidth(css::CSSKey key) { return Get<css::CSSLength>(key)->ToPixel(&m_CSSInfo, true); }
		inline float GetPixelHeight(css::CSSKey key) { return Get<css::CSSLength>(key)->ToPixel(&m_CSSInfo, false); }

		css::CSSBounds PositionInsideParent(const css::CSSBounds& space, const css::CSSBounds& initialSpace);
		void DrawBackgroundAndBorder(Renderer2D& renderer);
	};

} } }