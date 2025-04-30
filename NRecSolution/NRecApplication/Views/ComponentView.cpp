#include "ComponentView.h"
#include "ViewModels/ComponentViewModel.h"
#include "Views/CustomWidgets.h"

#include <QVBoxLayout>

ComponentView::ComponentView(ComponentViewModel *componentViewModel,
                             QWidget *parent)
    : QDialog{parent}, m_componentViewModel{componentViewModel}
{
    setAttribute(Qt::WA_DeleteOnClose);
    setWindowTitle(tr("Component Editor"));

    auto nameLabel = new Label(tr("Name"),this);
    nameLabel->setTypography(Typography::Caption1Strong);

    m_nameEdit = new LineEditExt(this);
    m_nameEdit->lineEdit()->setSizeScale(SizeScale::Small);

    auto massFlowLabel = new Label(tr("Mass Flow"),this);
    massFlowLabel->setTypography(Typography::Caption1Strong);

    m_massFlowSpin = new DoubleSpinBox(this);
    m_massFlowSpin->setSizeScale(SizeScale::Small);
    m_massFlowSpin->setDecimals(1);
    m_massFlowSpin->setMaximum(std::numeric_limits<int>::max());

    auto rotationalSpeedLabel = new Label(tr("Rotationals Speed"),this);
    rotationalSpeedLabel->setTypography(Typography::Caption1Strong);

    m_rotationalSpeedSpin = new DoubleSpinBox(this);
    m_rotationalSpeedSpin->setSizeScale(SizeScale::Small);
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

    connect(m_nameEdit, &LineEditExt::validEditingFinished,
            this, &ComponentView::onNameChanged);
    connect(m_massFlowSpin, &QDoubleSpinBox::valueChanged,
            this, &ComponentView::onMassFlowChanged);
    connect(m_rotationalSpeedSpin, &QDoubleSpinBox::valueChanged,
            this, &ComponentView::onRotationalSpeedChanged);
}

void ComponentView::onNameChanged()
{
    m_componentViewModel->setName(m_nameEdit->lineEdit()->text());
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
    if (m_nameEdit->lineEdit()->text() != name)
    {
        m_nameEdit->lineEdit()->setText(name);
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
