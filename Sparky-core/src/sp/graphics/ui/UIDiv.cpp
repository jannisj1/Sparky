#include "sp/sp.h"
#include "UIDiv.h"

#include "sp/graphics/FontManager.h"

namespace sp { namespace graphics { namespace ui {

	using namespace maths;

	UIDiv::UIDiv(Widget *parent, css::CSSManager* cssManager, tinyxml2::XMLElement *domElement, bool activatable, bool focusable)
		: Widget(parent, cssManager, domElement, activatable, focusable)
	{

	}

	void UIDiv::MoveBy(const maths::vec2& delta)
	{
		Widget::MoveBy(delta);
		for (auto c : m_Children)
		{
			c->MoveBy(delta);
		}
	}

	css::CSSBounds UIDiv::CalculatePosition(const css::CSSBounds& space, const css::CSSBounds& initialSpace)
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
		css::CSSContentJustification *cj = Get<css::CSSContentJustification>(JUSTIFY_CONTENT);
		css::CSSContentJustification *ai = Get<css::CSSContentJustification>(ALIGN_ITEMS);

		m_InnerBounds.x = space.x + marginLeft + borderLeftSize + paddingLeft;
		m_InnerBounds.y = space.y + marginTop + borderTopSize + paddingTop;

		m_InnerBounds.width = space.width - (m_InnerBounds.x - space.x) - marginRight - borderRightSize - paddingRight;
		m_InnerBounds.height = space.height - (m_InnerBounds.x - space.x) - paddingBottom - borderBottomSize - marginBottom;

		if (!fitChildrenWidth)
		{
			m_InnerBounds.width = GetPixelWidth(WIDTH);
		}

		if (!fitChildrenHeight)
		{
			m_InnerBounds.height = GetPixelHeight(HEIGHT);
		}
		
		CSSBounds childrenSpace = m_InnerBounds;

		m_ChildrenWrapSize.x = 0;
		m_ChildrenWrapSize.y = 0;

		for (auto c : m_Children)
		{
			if (c->Get<CSSDisplay>(DISPLAY)->Get() != CSSDisplay::NONE)
			{
				auto cPos = c->Get<CSSPosition>(POSITION)->Get();
				if (cPos == CSSPosition::ABSOLUTE || cPos == CSSPosition::FIXED)
					c->CalculatePosition(m_InnerBounds, m_InnerBounds);
				else
					childrenSpace = c->CalculatePosition(childrenSpace, m_InnerBounds);
			}
		}

		m_Bounds = space;
		m_Bounds.x += marginLeft;
		m_Bounds.y += marginTop;
		m_Bounds.width = m_InnerBounds.width + borderLeftSize + paddingLeft + paddingRight + borderRightSize;
		m_Bounds.height = m_InnerBounds.height + borderTopSize + paddingTop + paddingBottom + borderBottomSize;

		if (fitChildrenHeight)
		{
			float furthestDown = m_InnerBounds.y;
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
			float furthestLeft = m_InnerBounds.x;
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
		
		//TODO: space-around, space-between
		if (cj->Get() != CSSContentJustification::START)
		{
			if (fd->GetDirection() == CSSFlowDirection::RIGHT)
			{
				float currRowY = m_Children[0]->GetOuterBounds().y;
				int rowStartIndex = 0;
				float furthestRight = 0.0f;

				for (int i = 0; i < m_Children.size(); i++)
				{
					if (i < m_Children.size() - 1)
					{
						if (currRowY != m_Children[i + 1]->GetOuterBounds().y)
						{
							currRowY = m_Children[i + 1]->GetOuterBounds().y;
							goto rowEnd;
						}
					}
					else
					{
					rowEnd:
						if (cj->Get() == CSSContentJustification::END)
						{
							float furthestRight = m_Children[i]->GetOuterBounds().x + m_Children[i]->GetOuterBounds().width;
							float moveBy = m_InnerBounds.x + m_InnerBounds.width - furthestRight;

							for (int j = rowStartIndex; j <= i; j++)
								m_Children[j]->MoveBy(maths::vec2(moveBy, 0.0f));
						}
						else if (cj->Get() == CSSContentJustification::CENTER)
						{
							float furthestRight = m_Children[i]->GetOuterBounds().x + m_Children[i]->GetOuterBounds().width;
							float moveBy = m_InnerBounds.x + m_InnerBounds.width - furthestRight;
							moveBy /= 2.0f;

							for (int j = rowStartIndex; j <= i; j++)
								m_Children[j]->MoveBy(maths::vec2(moveBy, 0.0f));
						}

						rowStartIndex = i + 1;
					}
				}
			}
			else if (fd->GetDirection() == CSSFlowDirection::DOWN)
			{
				float currColX = m_Children[0]->GetOuterBounds().x;
				int colStartIndex = 0;

				for (int i = 0; i < m_Children.size(); i++)
				{
					if (i < m_Children.size() - 1)
					{
						if (currColX != m_Children[i + 1]->GetOuterBounds().x)
						{
							currColX = m_Children[i + 1]->GetOuterBounds().x;
							goto colEnd;
						}
					}
					else
					{
					colEnd:
						if (cj->Get() == CSSContentJustification::END)
						{
							float furthestDown = m_Children[i]->GetOuterBounds().y + m_Children[i]->GetOuterBounds().height;
							float moveBy = m_InnerBounds.y + m_InnerBounds.height - furthestDown;

							for (int j = colStartIndex; j <= i; j++)
								m_Children[j]->MoveBy(maths::vec2(0.0f, moveBy));
						}
						else if (cj->Get() == CSSContentJustification::CENTER)
						{
							float furthestDown = m_Children[i]->GetOuterBounds().y + m_Children[i]->GetOuterBounds().height;
							float moveBy = m_InnerBounds.y + m_InnerBounds.height - furthestDown;
							moveBy /= 2.0f;

							for (int j = colStartIndex; j <= i; j++)
								m_Children[j]->MoveBy(maths::vec2(0.0f, moveBy));
						}
						colStartIndex = i + 1;
					}
				}
			}
		}

		if (ai->Get() != CSSContentJustification::START)
		{
			if (fd->IsWrapping())
			{
				SP_WARN("no align-items support for wrapping flow-children yet :/");//TODO
				goto endContentJustification;
			}

			if (fd->GetDirection() == CSSFlowDirection::DOWN)
			{
				float startX = m_InnerBounds.x;
				float endX = startX + m_InnerBounds.width;

				if (ai->Get() == CSSContentJustification::CENTER)
				{
					float middle = (endX - startX) / 2.0f;
					for (auto c : m_Children)
					{
						c->MoveBy(vec2(middle - c->GetOuterBounds().width / 2.0f, 0.0f));
					}
				}
				else if (ai->Get() == CSSContentJustification::END)
				{
					for (auto c : m_Children)
					{
						c->MoveBy(vec2(endX - startX - c->GetOuterBounds().width, 0.0f));
					}
				}
			}
			else if (fd->GetDirection() == CSSFlowDirection::RIGHT)
			{
				float startY = m_InnerBounds.y;
				float endY = startY + m_InnerBounds.height;
				
				if (ai->Get() == CSSContentJustification::CENTER)
				{
					float middle = (endY - startY) / 2.0f;
					for (auto c : m_Children)
					{
						c->MoveBy(vec2(0.0f, middle - c->GetOuterBounds().height / 2.0f));
					}
				}
				else if (ai->Get() == CSSContentJustification::END)
				{
					for (auto c : m_Children)
					{
						c->MoveBy(vec2(0.0f, endY - startY - c->GetOuterBounds().height));
					}
				}
			}
		}
		endContentJustification:

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
			if(c->Get<css::CSSDisplay>(css::DISPLAY)->Get() != css::CSSDisplay::NONE)
				c->OnRender(renderer);
		}
	}

} } }