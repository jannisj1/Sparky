#include "sp/sp.h"
#include "UILayer.h"

#include "../Renderer2D.h"
#include "sp/app/Window.h"
#include "sp/app/Application.h"
#include "sp/graphics/ui/UIDiv.h"
#include "sp/graphics/ui/UIRoot.h"
#include "sp/graphics/ui/UILabel.h"
#include "sp/graphics/ui/UIButton.h"

namespace sp { namespace graphics {

	UILayer::UILayer()
	{
		float width = Application::GetApplication().GetWindowWidth();
		float height = Application::GetApplication().GetWindowHeight();

		m_Renderer = spnew Renderer2D(width, height);
		m_Scene = spnew Scene2D(maths::mat4::Orthographic(0, width, 0, height, -1.0f, 1.0f));
		m_Renderer->SetCamera(m_Scene->GetCamera());

		m_CSSManager = spnew css::CSSManager();
	}

	UILayer::~UILayer()
	{
		spdel m_Material;
		spdel m_Renderer;
		spdel m_RootWidget;
		spdel m_CSSManager;
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
		((Renderer2D*)m_Renderer)->SetScreenSize(maths::tvec2<uint>(width, height));
		m_Scene->GetRenderer()->SetScreenSize(maths::tvec2<uint>(width, height));
		return false;
	}

	void UILayer::FromXML(const String& xml)
	{
		String physicalPath;
		VFS::Get()->ResolvePhysicalPath(xml, physicalPath);
		tinyxml2::XMLDocument doc;
		tinyxml2::XMLError err = doc.LoadFile(physicalPath.c_str());
		if(err)
			SP_ERROR("tinyxml2-error ", (int)err);
		
		ui::Widget::FocusedWidget = nullptr;

		if(doc.FirstChildElement())
			m_RootWidget = CreateWidgetFromXML(nullptr, doc.FirstChildElement());
	}

	ui::Widget *UILayer::CreateWidgetFromXML(ui::Widget *parent, tinyxml2::XMLElement *domElement)
	{
		const std::string elemName = domElement->Name();
		ui::Widget *curr = nullptr;

		if (elemName == "ui") curr = spnew ui::UIRoot(parent, m_CSSManager, domElement);
		else if (elemName == "div") curr = spnew ui::UIDiv(parent, m_CSSManager, domElement);
		else if (elemName == "label") curr = spnew ui::UILabel(parent, m_CSSManager, domElement);
		//else if (elemName == "button") curr = spnew ui::UIButton(parent, m_CSSManager, domElement);
		else if (elemName == "style")
		{
			if (domElement->Attribute("src"))
			{
				m_CSSManager->EvalCSS(VFS::Get()->ReadTextFile(domElement->Attribute("src")));
			}
			else
			{
				const char *t = domElement->GetText();
				m_CSSManager->EvalCSS((t == nullptr ? "" : t));
			}
		}
		else SP_ERROR("Unknown UI-Element: ", elemName);

		tinyxml2::XMLElement *child = domElement->FirstChildElement();

		if(curr)
			while (child != nullptr)
			{
				ui::Widget *childWidget = CreateWidgetFromXML(curr, child);
				if(childWidget)
					curr->AddChild(childWidget);
				child = child->NextSiblingElement();
			}

		return curr;
	}

	void UILayer::OnUpdateInternal(const Timestep& ts)
	{
		maths::vec2 saveScale = FontManager::GetScale();
		FontManager::SetScale(maths::vec2(1, 1));
		css::CSSBounds space(0, 0, Application::GetApplication().GetWindowWidth(), Application::GetApplication().GetWindowHeight());
		m_RootWidget->CalculatePosition(space, space);
		
		FontManager::SetScale(saveScale); 
		
		OnUpdate(ts);
	}


	void UILayer::OnRender()
	{
		maths::vec2 saveScale = FontManager::GetScale();
		FontManager::SetScale(maths::vec2(1, 1));

		m_Scene->OnRender();

		m_Renderer->Begin();
		
		m_RootWidget->OnRender(*m_Renderer);

		m_Renderer->End();
		m_Renderer->Present();

		OnRender(*m_Renderer);

		FontManager::SetScale(saveScale);
	}

	void UILayer::OnRender(Renderer2D& renderer)
	{

	}

	void UILayer::OnEvent(events::Event& event)
	{

	}

	bool UILayer::OnMouseMovedEvent(events::MouseMovedEvent & event)
	{
		return m_RootWidget->OnMouseMoved(event);
	}

	bool UILayer::OnMousePressedEvent(events::MousePressedEvent& event)
	{
		return m_RootWidget->OnMousePressed(event);
	}

	bool UILayer::OnMouseReleasedEvent(events::MouseReleasedEvent& event)
	{
		return m_RootWidget->OnMouseReleased(event);
	}

	bool UILayer::OnWindowResizeEvent(events::ResizeWindowEvent& event)
	{
		//TODO: Not workin wtf
		m_Scene->GetCamera()->SetProjectionMatrix(maths::mat4::Orthographic(0, event.GetWidth(), 0, event.GetHeight(), -1.0f, 1.0f));
		return false;
	}

} }