#include "ComponentView.h"
#include "ViewModels/ComponentViewModel.h"

#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QLabel>

ComponentView::ComponentView(ComponentViewModel *componentViewModel,
                             QWidget *parent)
    : QDialog{parent}, m_componentViewModel{componentViewModel}
{
    setAttribute(Qt::WA_DeleteOnClose);

    auto nameLabel = new QLabel(tr("Name"),this);
    m_nameEdit = new QLineEdit(this);

    auto massFlowLabel = new QLabel(tr("Mass Flow"),this);
    m_massFlowSpin = new QDoubleSpinBox(this);
    m_massFlowSpin->setDecimals(1);
    m_massFlowSpin->setMaximum(std::numeric_limits<int>::max());

    auto rotationalSpeedLabel = new QLabel(tr("Rotationals Speed"),this);
    m_rotationalSpeedSpin = new QDoubleSpinBox(this);
    m_rotationalSpeedSpin->setDecimals(0);
    m_rotationalSpeedSpin->setMaximum(std::numeric_limits<int>::max());

    auto vLayout = new QVBoxLayout();
    vLayout->addWidget(nameLabel);
    vLayout->addWidget(m_nameEdit);
    vLayout->addWidget(massFlowLabel);
    vLayout->addWidget(m_massFlowSpin);
    vLayout->addWidget(rotationalSpeedLabel);
    vLayout->addWidget(m_rotationalSpeedSpin);

    setLayout(vLayout);

    setName(componentViewModel->getName());
    setMassFlow(componentViewModel->getMassFlow());
    setRotationalSpeed(componentViewModel->getRotationalSpeed());

    connect(componentViewModel, &ComponentViewModel::nameChanged,
            this, &ComponentView::setName);
    connect(componentViewModel, &ComponentViewModel::massFlowChanged,
            this, &ComponentView::setMassFlow);
    connect(componentViewModel, &ComponentViewModel::rotationalSpeedChanged,
            this, &ComponentView::setRotationalSpeed);

    connect(m_nameEdit, &QLineEdit::editingFinished,
            this, &ComponentView::onNameChanged);
    connect(m_massFlowSpin, &QDoubleSpinBox::valueChanged,
            this, &ComponentView::setMassFlow);
    connect(m_rotationalSpeedSpin, &QDoubleSpinBox::valueChanged,
            this, &ComponentView::setRotationalSpeed);
}

void ComponentView::onNameChanged()
{
    m_componentViewModel->setName(m_nameEdit->text());
}

void ComponentView::onMassFlowChanged()
{
    m_componentViewModel->setMassFlow(m_massFlowSpin->value());
}

void ComponentView::onRotationalSpeedChanged()
{
    m_componentViewModel->setRotationalSpeed(m_rotationalSpeedSpin->value());
}

void ComponentView::setName(const QString& name)
{
    if (m_nameEdit->text() != name)
    {
        m_nameEdit->setText(name);
    }
}

void ComponentView::setMassFlow(const double& massFlow)
{
    if (m_massFlowSpin->value() != massFlow)
    {
        m_massFlowSpin->setValue(massFlow);
    }
}

void ComponentView::setRotationalSpeed(const double& rotationalSpeed)
{
    if (m_rotationalSpeedSpin->value() != rotationalSpeed)
    {
        m_rotationalSpeedSpin->setValue(rotationalSpeed);
    }
}
