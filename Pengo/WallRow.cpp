#include "WallRow.h"
#include "BoxCollider.h"
#include "Transform.h"


WallRow::WallRow(glm::vec2 startingPos, glm::vec2 size)
	: m_StartingPos(startingPos)
	, m_Size(size)
	, m_WallSize(8, 8)
{
	GetComponent<Transform>()->SetWorldPosition(m_StartingPos);

	//auto amountOfwallsX = roundf(m_Size.x / m_WallSize.x);
	//auto amountOfWallsY = roundf(m_Size.y / m_WallSize.y);

	for (float i{}; i < m_Size.x; i += m_WallSize.x)
	{
		for (float j{}; j < m_Size.y; j += m_WallSize.y)
		{
			auto wall = new Wall();
			wall->SetParent(this, false);
			wall->GetComponent<Transform>()->SetWorldPosition(glm::vec2(i, j) + m_StartingPos);
		}
	}


	auto collider = AddComponent<BoxCollider>();
	collider->SetColliderSize(m_Size);
	collider->DebugRender(true);
}
