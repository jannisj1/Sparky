#pragma once

#include "sp/sp.h"
#include "Panel.h"

#include "sp/maths/maths.h"

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
		
		String m_Name;
		String m_ID;
		std::vector<String> m_Classes;

	public:
		Widget(String name)
		: m_Name(name) { }
	
	public:
		virtual bool OnMousePressed(events::MousePressedEvent& e);
		virtual bool OnMouseReleased(events::MouseReleasedEvent& e);
		virtual bool OnMouseMoved(events::MouseMovedEvent& e);

		virtual void OnUpdate();
		virtual void OnRender(Renderer2D& renderer);

		inline const maths::Rectangle& GetBounds() const { return m_Bounds; }
		inline maths::Rectangle& GetBounds() { return m_Bounds; }
		inline void SetBounds(const maths::Rectangle& bounds) { m_Bounds = bounds; }
		
		inline const String& GetName() const { return m_Name; }
		inline const std::vector<String> GetClasses() const { return m_Classes; }
		inline const String& GetID() const { return m_ID; }

		inline bool IsActive() const { return m_State == ACTIVE; }
	};

} } }