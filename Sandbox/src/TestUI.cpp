#include "TestUI.h"

using namespace sp;
using namespace graphics;
using namespace events;
using namespace entity;
using namespace component;
using namespace maths;
using namespace API;

TestUI::TestUI()
	: UILayer()
{
	m_Renderer = nullptr;
}

TestUI::~TestUI()
{

}

void TestUI::OnInit(Renderer2D& renderer, Material& material)
{
	FromXML("/ui/TestUI.xml");

	// m_Window->SetVsync(false);
	m_Renderer = &renderer;

	renderer.SetRenderTarget(RenderTarget::SCREEN);
	//renderer.AddPostEffectsPass(new PostEffectsPass(Shader::CreateFromFile("Horizontal Blur", "shaders/postfx.shader")));
	//renderer.SetPostEffects(false);

	FontManager::Add(spnew Font("Consolas", "res/consola.ttf", 96));
	FontManager::Add(spnew Font("Brush Script", "res/BrushScriptStd.otf", 96));
}

void TestUI::OnTick()
{
	
}

void TestUI::OnUpdate(const Timestep& ts)
{

}

void TestUI::OnEvent(sp::events::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<MousePressedEvent>(METHOD(&UILayer::OnMousePressedEvent));
	dispatcher.Dispatch<MouseMovedEvent>(METHOD(&UILayer::OnMouseMovedEvent));
	dispatcher.Dispatch<MouseReleasedEvent>(METHOD(&UILayer::OnMouseReleasedEvent));
	dispatcher.Dispatch<ResizeWindowEvent>(METHOD(&UILayer::OnWindowResizeEvent));
}

void TestUI::OnRender(Renderer2D& renderer)
{

}
