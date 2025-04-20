#include "NRecLib.h"
#include <iostream>

using namespace nrec;

Component::Component(const std::string &name)
    : m_name(name)
{
}

std::string Component::name() const
{
    return m_name;
}

double Component::massFlow() const
{
    return m_massFlow;
}

double Component::rotationalSpeed() const
{
    return m_rotationalSpeed;
}

void Component::setName(const std::string &name)
{
    m_name = name;
}

void Component::setMassFlow(const double& massFlow)
{
    m_massFlow = massFlow;
}

void Component::setRotationalSpeed(const double& rotationalSpeed)
{
    m_rotationalSpeed = rotationalSpeed;
}

size_t ComponentList::numberOfComponents() const
{
    return m_components.size();
}

Component* ComponentList::getComponent(const int number) const
{
    return number < m_components.size() ? m_components.at(number).get() : nullptr;
}

Component* ComponentList::getComponent(const std::string &name) const
{
    auto itr = std::find_if(m_components.begin(), m_components.end(),
                            [&](const std::shared_ptr<Component>& component) {
                                return component->name() == name;
                            });

    return itr != m_components.end() ? itr->get() : nullptr;
}

bool ComponentList::addComponent(const std::string &name)
{
    auto pComponent = std::make_shared<Component>(name);
    m_components.push_back(pComponent);

    return true;
}

bool ComponentList::deleteComponent(const std::string &name)
{
    auto itr = std::find_if(m_components.begin(), m_components.end(),
                            [&](const std::shared_ptr<Component>& component) {
                                return component->name() == name;
                            });

    if (itr != m_components.end())
    {
        m_components.erase(itr);        

        return true;
    }

    return false;
}
