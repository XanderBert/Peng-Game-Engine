#pragma once
#include "GameObject.h"

class Wall final : public GameObject
{
public:
	Wall();
	virtual ~Wall() override;

	Wall(const Wall& other) = delete;
	Wall(Wall&& other)noexcept = delete;
	Wall& operator=(const Wall& other) = delete;
	Wall& operator=(Wall&& other)noexcept = delete;
};
