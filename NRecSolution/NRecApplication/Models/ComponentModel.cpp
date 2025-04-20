#include "ComponentModel.h"
#include "NRecLib.h"

ComponentModel::ComponentModel(nrec::Component *component,
                               QObject *parent)
    : QObject{parent}, m_component{component}
{
}

std::string ComponentModel::getName() const
{
    return m_component->name();
}

double ComponentModel::getMassFlow() const
{
    return m_component->massFlow();
}

double ComponentModel::getRotationalSpeed() const
{
    return m_component->rotationalSpeed();
}

void ComponentModel::setName(const std::string &name)
{
    if (m_component->name() != name)
    {
        m_component->setName(name);

        emit nameChanged(QString::fromStdString(name));
    }
}

void ComponentModel::setMassFlow(const double &massFlow)
{
    if (m_component->massFlow() != massFlow)
    {
        m_component->setMassFlow(massFlow);

        emit massFlowChanged(massFlow);
    }
}

void ComponentModel::setRotationalSpeed(const double &rotationalSpeed)
{
    if (m_component->rotationalSpeed() != rotationalSpeed)
    {
        m_component->setRotationalSpeed(rotationalSpeed);

        emit rotationalSpeedChanged(rotationalSpeed);
    }
}
