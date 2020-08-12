#pragma once
#include "RenderComponet.h"
#include "../Graphics/Texture.h"

namespace nc
{
	class SpriteComponet : public RenderComponet
	{
	public:
		// Inherited via RenderComponet
		virtual bool Create(void* data = nullptr) override;
		virtual void Destroy() override;

		virtual void Update() override;
		virtual void Draw() override;

	protected:
		class Texture* m_texture{};
	};
}
