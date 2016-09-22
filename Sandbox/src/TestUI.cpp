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
	FromXML("ui/TestUI.xml");

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
	using namespace sp::internal;

}

void TestUI::OnUpdate(const Timestep& ts)
{

}

bool TestUI::OnKeyPressedEvent(KeyPressedEvent& event)
{
	if (!m_Renderer)
		return false;

	Renderer2D& renderer = *m_Renderer;

	if (event.GetRepeat())
		return false;

	if (event.GetKeyCode() == SP_KEY_T)
	{
		renderer.SetRenderTarget(renderer.GetRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
		return true;
	}
	if (event.GetKeyCode() == SP_KEY_P)
	{
		renderer.SetPostEffects(!renderer.GetPostEffects());
		return true;
	}

	return false;
}

bool TestUI::OnMousePressedEvent(MousePressedEvent& event)
{
	return false;
}

void TestUI::OnEvent(sp::events::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(METHOD(&TestUI::OnKeyPressedEvent));
	dispatcher.Dispatch<MousePressedEvent>(METHOD(&TestUI::OnMousePressedEvent));
}

void TestUI::OnRender(Renderer2D& renderer)
{

}
