#include "pch.h"
#include "ObjectFactory.h"
#include "Componet/PhysicsComponet.h"
#include "Componet/SpriteComponet.h"
#include "Componet/SpriteAnimationComponent.h"
#include "Componet/RigidBodyComponent.h"
#include "Componet/AudioComponent.h"

namespace nc
{
	void nc::ObjectFactoryImpl::Initialize()
	{
		
		ObjectFactory::Instance().Register("GameObject", new Creator<GameObject, Object>);
		ObjectFactory::Instance().Register("PhysicsComponent", new Creator<PhysicsComponet, Object>);
		ObjectFactory::Instance().Register("SpriteComponent", new Creator<SpriteComponet, Object>);
		ObjectFactory::Instance().Register("SpriteAnimationComponent", new Creator<SpriteAnimationComponent, Object>);
		ObjectFactory::Instance().Register("RigidBodyComponent", new Creator<RigidBodyComponent, Object>);
		ObjectFactory::Instance().Register("AudioComponent", new Creator<AudioComponent, Object>);
	}
}

