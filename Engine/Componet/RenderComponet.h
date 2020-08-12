#pragma once
#include "Componet.h"

namespace nc
{
	class RenderComponet : public Componet
	{
	public:
		virtual void Draw() = 0;
	};
}