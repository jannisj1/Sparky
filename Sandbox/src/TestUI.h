#pragma once

#include <Sparky.h>
#include <sp/maths/maths.h>

class TestUI : public sp::graphics::UILayer
{
private:
	sp::graphics::Renderer2D* m_Renderer;

	double m_TestVal;
	sp::maths::vec2 m_MyVec2 = sp::maths::vec2(20.2, 40.9);
	sp::maths::vec3 m_MyVec3 = sp::maths::vec3(20, 40.6, 80);

public:
	TestUI();
	~TestUI();

	void OnInit(sp::graphics::Renderer2D& renderer, sp::graphics::Material& material) override;

	void OnTick() override;
	void OnUpdate(const sp::Timestep& ts) override;

	void OnEvent(sp::events::Event& event) override;

	void OnRender(sp::graphics::Renderer2D& renderer) override;
};