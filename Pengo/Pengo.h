#pragma once
#include "GameActor.h"

class Pengo final : public GameActor
{
public:
	Pengo();
	virtual ~Pengo() override;

	//Called each frame
	virtual void Update() override;
};
