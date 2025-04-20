#include "ComponentViewModel.h"

ComponentViewModel::ComponentViewModel(ComponentModel *componentModel,
                                       QObject *parent)
    : QObject{parent}, m_componentModel{componentModel}
{
    connect(componentModel, &ComponentModel::nameChanged,
            this, &ComponentViewModel::setName);
    connect(componentModel, &ComponentModel::massFlowChanged,
            this, &ComponentViewModel::setMassFlow);
    connect(componentModel, &ComponentModel::rotationalSpeedChanged,
            this, &ComponentViewModel::setRotationalSpeed);
}

void ComponentViewModel::setName(const QString& name)
{
    if (m_name != name)
    {
        m_name = name;
        m_componentModel->setName(name.toStdString());

        emit nameChanged(name);
    }
}

void ComponentViewModel::setMassFlow(const double &massFlow)
{
    if (m_massFlow != massFlow)
    {
        m_massFlow = massFlow;
        m_componentModel->setMassFlow(massFlow);

        emit massFlowChanged(massFlow);
    }
}

void ComponentViewModel::setRotationalSpeed(const double& rotationalSpeed)
{
    if (m_rotationalSpeed != rotationalSpeed)
    {
        m_rotationalSpeed = rotationalSpeed;
        m_componentModel->setRotationalSpeed(rotationalSpeed);

        emit rotationalSpeedChanged(rotationalSpeed);
    }
}

QString ComponentViewModel::getName() const
{
    return QString::fromStdString(m_componentModel->getName());
}

double ComponentViewModel::getMassFlow() const
{
    return m_componentModel->getMassFlow();
}

double ComponentViewModel::getRotationalSpeed() const
{
    return m_componentModel->getRotationalSpeed();
}
