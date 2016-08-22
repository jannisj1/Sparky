#include "sp/sp.h"
#include "UILayer.h"

#include "../BatchRenderer2D.h"
#include "sp/app/Window.h"
#include "sp/app/Application.h"

namespace sp { namespace graphics {

	UILayer::UILayer(const maths::mat4& projectionMatrix)
	{
		float width = Application::GetApplication().GetWindowWidth();
		float height = Application::GetApplication().GetWindowHeight();

		m_Renderer = spnew BatchRenderer2D(width, height);
		m_Scene = spnew Scene2D(projectionMatrix);
		m_Renderer->SetCamera(m_Scene->GetCamera());
	}

	UILayer::UILayer(Scene2D* scene)
		: m_Scene(scene)
	{
		float width = Application::GetApplication().GetWindowWidth();
		float height = Application::GetApplication().GetWindowHeight();

		m_Renderer = spnew BatchRenderer2D(width, height);
		m_Renderer->SetCamera(m_Scene->GetCamera());
		
	}

	UILayer::~UILayer()
	{
		spdel m_Material;
		spdel m_Renderer;
	}

	void UILayer::Init()
	{
		OnInit(*m_Renderer, *m_Material);
	}

	void UILayer::OnInit(Renderer2D& renderer, Material& material)
	{
	}

	Sprite* UILayer::Add(Sprite* sprite)
	{
		m_Scene->Add(spnew entity::Entity(sprite, maths::mat4::Translate(sprite->GetPosition())));
		return sprite;
	}

	Renderable2D* UILayer::Submit(Renderable2D* renderable)
	{
		m_SubmittedRenderables.push_back(renderable);
		return renderable;
	}

	bool UILayer::OnResize(uint width, uint height)
	{
		((BatchRenderer2D*)m_Renderer)->SetScreenSize(maths::tvec2<uint>(width, height));
		m_Scene->GetRenderer()->SetScreenSize(maths::tvec2<uint>(width, height));
		return false;
	}

	void UILayer::OnUpdateInternal(const Timestep& ts)
	{
		OnUpdate(ts);
	}

	void UILayer::OnRender()
	{
		m_Scene->OnRender();

		m_Renderer->Begin();
		
		for (const Renderable2D* renderable : m_SubmittedRenderables)
			renderable->Submit(m_Renderer);

		m_Renderer->End();
		m_Renderer->Present();

		OnRender(*m_Renderer);

		m_SubmittedRenderables.clear();
	}

	void UILayer::OnRender(Renderer2D& renderer)
	{
	}

} }