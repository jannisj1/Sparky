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
		Renderer2D* m_Renderer;
	protected:
		Material* m_Material;
		Scene2D* m_Scene;
		ui::Widget* m_RootWidget = nullptr;

		css::CSSManager *m_CSSManager;

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
	protected:
		bool OnResize(uint width, uint height) override;

	private:
		ui::Widget* CreateWidgetFromXML(tinyxml2::XMLElement *domElement);

	};	

} }