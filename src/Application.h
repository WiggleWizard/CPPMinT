#pragma once

#include "ApplicationBase.h"


class Application : public ApplicationBase
{
private:
	using Super = ApplicationBase;

public:
	virtual void Initialize() override;
	virtual void DrawImGui(double deltaTime) override;
};