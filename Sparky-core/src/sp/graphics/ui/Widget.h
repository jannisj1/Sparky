#pragma once
#include "sp/sp.h"

#include "sp/maths/maths.h"
#include "sp/css/CSSManager.h"
#include "sp/graphics/Renderable2D.h"
#include "sp/css/CSSBounds.h"
#include "sp/graphics/Renderer2D.h"

#include <SparkyCSS/SparkyCSS.h>
#include <sp/js/SparkyJS.h>
#include <tinyxml2.h>

namespace sp { namespace graphics { namespace ui {

	class SP_API Widget : public spjs::DomElement
	{
	protected:
		css::CSSBounds m_Bounds;
		css::CSSManager *m_CSSManager;
		tinyxml2::XMLElement *m_DOMElement;
		std::vector<Widget*> m_Children;
		bool m_Activatable, m_Focusable;
		css::CSSBounds &m_InnerBounds = m_CSSInfo.InnerBounds;
		css::CSSBounds m_OuterBounds;
		Widget *m_Parent;
		spjs::ExecutionEngine *m_JS = nullptr;
		maths::vec2 m_RelativePos;
		std::unordered_map<sp::css::CSSKey, sp::css::CSSValue*> m_PrivateCSSRules;

	public:
		Widget(Widget *parent, css::CSSManager *cssManager, tinyxml2::XMLElement *domElement, bool activatable = false, bool focusable = false);
		~Widget();

	public:
		static ui::Widget *FocusedWidget;
		virtual bool OnMousePressed(events::MousePressedEvent& e);
		virtual bool OnMouseReleased(events::MouseReleasedEvent& e);
		virtual bool OnMouseMoved(events::MouseMovedEvent& e);

		virtual css::CSSBounds CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace) = 0;
		virtual void PostProcessPosition();
		virtual void OnRender(Renderer2D& renderer);
		
		inline void SetEE(spjs::ExecutionEngine *ee) { m_JS = ee; }

		inline css::UIElementCSSInfo &GetCSSInfo() { return m_CSSInfo; }
		inline const css::CSSValue *GetCSSValue(css::CSSKey key) { return m_CSSManager->GetValue(m_PrivateCSSRules, m_CSSInfo, key); }
		
		inline void AddChild(ui::Widget *child) { m_Children.push_back(child); m_DomChildren.push_back(child); }
		inline std::vector<ui::Widget*>& GetChildren() { return m_Children; }

		inline const css::CSSBounds& GetOuterBounds() const { return m_OuterBounds; }

		virtual void MoveBy(const maths::vec2& delta);

		template<class T>
		inline T *Get(css::CSSKey key) { return m_CSSManager->Get<T>(m_PrivateCSSRules, m_CSSInfo, key); }
		
		maths::vec2 m_ChildrenWrapSize;
		
		void SetCSSProperties(const String& css) override;

	protected:
		inline float GetPixelWidth(css::CSSKey key) { return Get<css::CSSLength>(key)->ToPixel(&m_CSSInfo, true); }
		inline float GetPixelHeight(css::CSSKey key) { return Get<css::CSSLength>(key)->ToPixel(&m_CSSInfo, false); }

		css::CSSBounds PositionInsideParent(const css::CSSBounds& space, const css::CSSBounds& initialSpace);
		void DrawBackgroundAndBorder(Renderer2D& renderer);

		String GetDOMValue(const String& name);
	};

} } }