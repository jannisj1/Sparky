#include "sp/sp.h"
#include "UIDiv.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UIDiv::UIDiv(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement)
		: Widget(parent, cssManager, domElement)
	{

	}

	css::CSSBounds UIDiv::OnUpdate(const css::CSSBounds& space, const css::CSSBounds& initialSpace)
	{
		using namespace css;

		float marginLeft = GetPixelWidth(MARGIN_LEFT),
			marginRight = GetPixelWidth(MARGIN_RIGHT),
			marginTop = GetPixelHeight(MARGIN_TOP),
			marginBottom = GetPixelHeight(MARGIN_BOTTOM);

		float paddingLeft = GetPixelWidth(PADDING_LEFT),
			paddingRight = GetPixelWidth(PADDING_RIGHT),
			paddingTop = GetPixelHeight(PADDING_TOP),
			paddingBottom = GetPixelHeight(PADDING_BOTTOM);

		float borderLeftSize = GetPixelWidth(BORDER_LEFT_WIDTH),
			borderRightSize = GetPixelWidth(BORDER_RIGHT_WIDTH),
			borderTopSize = GetPixelHeight(BORDER_TOP_WIDTH),
			borderBottomSize = GetPixelHeight(BORDER_BOTTOM_WIDTH);

		bool fitChildrenWidth = Get<CSSLength>(WIDTH)->FitChildren();
		bool fitChildrenHeight = Get<CSSLength>(HEIGHT)->FitChildren();

		css::CSSFlowDirection *fd = Get<css::CSSFlowDirection>(FLOW_CHILDREN);

		m_InnerBounds.x = space.x + marginLeft + borderLeftSize + paddingLeft;
		m_InnerBounds.y = space.y + marginTop + borderTopSize + paddingTop;

		if (fitChildrenWidth)
		{
			m_InnerBounds.width = space.width - (m_InnerBounds.x - space.x) - marginRight - borderRightSize - paddingRight;
		}
		else
		{
			m_InnerBounds.width = GetPixelWidth(WIDTH);
		}

		if (fitChildrenHeight)
		{
			m_InnerBounds.height = space.height - (m_InnerBounds.x - space.x) - paddingBottom - borderBottomSize - marginBottom;
		}
		else
		{
			m_InnerBounds.height = GetPixelHeight(HEIGHT);
		}
		
		CSSBounds childrenSpace = m_InnerBounds;

		for (auto c : m_Children)
		{
			childrenSpace = c->OnUpdate(childrenSpace, m_InnerBounds);
		}

		m_Bounds = space;
		m_Bounds.x += marginLeft;
		m_Bounds.y += marginTop;
		m_Bounds.width = m_InnerBounds.width + borderLeftSize + paddingLeft + paddingRight + borderRightSize;
		m_Bounds.height = m_InnerBounds.height + borderTopSize + paddingTop + paddingBottom + borderBottomSize;

		if (fitChildrenHeight)
		{
			float furthestDown = m_InnerBounds.y; //TODO: Add furthest up for flow direction UP
			for (auto c : m_Children)
			{
				furthestDown = (c->GetOuterBounds().y + c->GetOuterBounds().height) > furthestDown ? (c->GetOuterBounds().y + c->GetOuterBounds().height) : furthestDown;
			}

			if (furthestDown < m_InnerBounds.y + m_InnerBounds.height)
			{
				float shrinkDifferential = (m_InnerBounds.y + m_InnerBounds.height) - furthestDown;
				m_Bounds.height -= shrinkDifferential;
				m_InnerBounds.height -= shrinkDifferential;
			}
		}

		if (fitChildrenWidth)
		{
			float furthestLeft = m_InnerBounds.x; //TODO: Add furthest right for flow direction LEFT
			for (auto c : m_Children)
			{
				furthestLeft = (c->GetOuterBounds().x + c->GetOuterBounds().width) > furthestLeft ? (c->GetOuterBounds().x + c->GetOuterBounds().width) : furthestLeft;
			}

			if (furthestLeft < m_InnerBounds.x + m_InnerBounds.width)
			{
				float shrinkDifferential = (m_InnerBounds.x + m_InnerBounds.width) - furthestLeft;
				m_Bounds.width -= shrinkDifferential;
				m_InnerBounds.width -= shrinkDifferential;
			}
		}
		
		m_OuterBounds = m_Bounds;
		m_OuterBounds.x -= marginLeft;
		m_OuterBounds.y -= marginTop;
		m_OuterBounds.width += marginLeft + marginRight;
		m_OuterBounds.height += marginTop + marginBottom;

		if (m_Parent)
			return PositionInsideParent(space, initialSpace);
		else
			return css::CSSBounds();
	}

	void UIDiv::OnRender(Renderer2D& renderer)
	{
		DrawBackgroundAndBorder(renderer);

		for (auto c : m_Children)
		{
			c->OnRender(renderer);
		}
	}

} } }