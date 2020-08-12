#include "pch.h"
#include "GameObject.h"
#include "Componet/Componet.h"
#include "Componet/RenderComponet.h"

namespace nc
{

    bool nc::GameObject::Create(void* data)
    {
        m_engine = static_cast<Engine*>(data);
        return true;
    }
    
    void nc::GameObject::Destroy()
    {

    }
    void GameObject::AddComponet(Componet* componet)
    {
        componet->m_owner = this;
        m_componets.push_back(componet);
    }
    void GameObject::RemoveComponet(Componet* componet)
    {
        auto iter = std::find(m_componets.begin(), m_componets.end(), componet);
        if (iter != m_componets.end())
        {
            (*iter)->Destroy();
            delete(*iter);
        }
    }
    void GameObject::RemoveAlComponet()
    {
        for (auto componet : m_componets)
        {
            componet->Destroy();
            delete componet;
        }
        m_componets.clear();
    }
    void GameObject::Update()
    {
        for (auto componet : m_componets)
        {
            componet->Update();
        }

    }
    void GameObject::Draw()
    {
        RenderComponet* componet = GetComponet<RenderComponet>();
        if (componet)
        {
            componet->Draw();
        }
    }
}
