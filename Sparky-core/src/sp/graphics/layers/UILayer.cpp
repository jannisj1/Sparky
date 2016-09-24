#include "sp/sp.h"
#include "UILayer.h"

#include "../BatchRenderer2D.h"
#include "sp/app/Window.h"
#include "sp/app/Application.h"
#include "sp/graphics/ui/UILabel.h"

namespace sp { namespace graphics {

	UILayer::UILayer()
	{
		float width = Application::GetApplication().GetWindowWidth();
		float height = Application::GetApplication().GetWindowHeight();

		m_Renderer = spnew BatchRenderer2D(width, height);
		m_Scene = spnew Scene2D(maths::mat4::Orthographic(0, width, 0, height, -1.0f, 1.0f));
		m_Renderer->SetCamera(m_Scene->GetCamera());
	}

	UILayer::~UILayer()
	{
		spdel m_Material;
		spdel m_Renderer;
		spdel m_RootWidget;
	}

	void UILayer::Init()
	{
		OnInit(*m_Renderer, *m_Material);
	}

	void UILayer::OnInit(Renderer2D& renderer, Material& material)
	{
	}

	bool UILayer::OnResize(uint width, uint height)
	{
		((BatchRenderer2D*)m_Renderer)->SetScreenSize(maths::tvec2<uint>(width, height));
		m_Scene->GetRenderer()->SetScreenSize(maths::tvec2<uint>(width, height));
		return false;
	}

	void UILayer::FromXML(const String& xml)
	{
		//m_CSSManager.EvalCSS(VFS::Get()->ReadTextFile("/ui/TestCSS.css"));
		//m_RootWidget = new ui::UILabel(&m_CSSManager, "How are you doin' dev? :)", maths::vec2(50, 50), 24);
		
		tinyxml2::XMLDocument doc;
		
		String out;
		VFS::Get()->ResolvePhysicalPath("/ui/", out);
		SP_ERROR(out);
	}

	void UILayer::OnUpdateInternal(const Timestep& ts)
	{
		m_RootWidget->OnUpdate();
		OnUpdate(ts);
	}

	void UILayer::OnRender()
	{
		maths::vec2 saveScale = FontManager::GetScale();
		FontManager::SetScale(maths::vec2(1, 1));

		m_Scene->OnRender();

		m_Renderer->Begin();
		
		SP_ASSERT(m_RootWidget);
		m_RootWidget->OnRender(*m_Renderer);

		m_Renderer->End();
		m_Renderer->Present();

		OnRender(*m_Renderer);

		FontManager::SetScale(saveScale);
	}

	void UILayer::OnRender(Renderer2D& renderer)
	{
	}

} }