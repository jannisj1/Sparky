#pragma once

#include <Sparky.h>

class TestUI : public sp::graphics::UILayer
{
private:
	sp::graphics::Renderer2D* m_Renderer;
public:
	TestUI();
	~TestUI();

	void OnInit(sp::graphics::Renderer2D& renderer, sp::graphics::Material& material) override;

	void OnTick() override;
	void OnUpdate(const sp::Timestep& ts) override;

	void OnEvent(sp::events::Event& event) override;

	void OnRender(sp::graphics::Renderer2D& renderer) override;
};