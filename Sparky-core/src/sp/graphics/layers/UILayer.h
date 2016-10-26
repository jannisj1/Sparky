#pragma once
#include "Layer.h"

#include "sp/sp.h"

#include "sp/Scene2D.h"
#include "sp/events/Event.h"
#include "sp/graphics/Renderable2D.h"
#include "sp/graphics/Mask.h"
#include "sp/graphics/ui/Widget.h"

#include <tinyxml2.h>

namespace sp { namespace graphics {

	class SP_API UILayer : public Layer
	{
	private:
		Renderer2D *m_Renderer;
	protected:
		Material *m_Material;
		Scene2D *m_Scene;
		ui::Widget *m_RootWidget = nullptr;

		tinyxml2::XMLDocument *m_Doc = nullptr;
		css::CSSManager *m_CSSManager = nullptr;
		spjs::ExecutionEngine *m_EE = nullptr;

		double m_TestValue = 123.45;
		const double m_TestValue2 = 23987.349587;

	public:
		UILayer();
		virtual ~UILayer();

		virtual void Init();
		virtual void OnInit(Renderer2D& renderer, Material& material);
		void FromXML(const String& xml);

		inline void SetMask(const Mask* mask) const { m_Renderer->SetMask(mask); }
		inline Scene2D* GetScene() { return m_Scene; }

		void OnUpdateInternal(const Timestep& ts) override;
		virtual void OnRender(Renderer2D& renderer);
		void OnRender() override;
		void OnEvent(events::Event& event) override;

		bool OnMouseMovedEvent(events::MouseMovedEvent& event);
		bool OnMousePressedEvent(events::MousePressedEvent& event);
		bool OnMouseReleasedEvent(events::MouseReleasedEvent& event);
		bool OnWindowResizeEvent(events::ResizeWindowEvent& event);

	protected:
		bool OnResize(uint width, uint height) override;

	private:
		ui::Widget* CreateWidgetFromXML(ui::Widget *parent, tinyxml2::XMLElement *domElement);

	};	

} }