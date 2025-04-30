#ifndef COMPONENTVIEW_H
#define COMPONENTVIEW_H

#include <QDialog>

class ComponentViewModel;
class DoubleSpinBox;
class LineEditExt;

class ComponentView : public QDialog
{
    Q_OBJECT
public:
    explicit ComponentView(ComponentViewModel* componentViewModel,
                           QWidget *parent = nullptr);
private:
    void onNameChanged();
    void onMassFlowChanged();
    void onRotationalSpeedChanged();

    void setName(const QString& name);
    void setMassFlow(const double& massFlow);
    void setRotationalSpeed(const double& rotationalSpeed);

private:
    ComponentViewModel* m_componentViewModel{nullptr};
    LineEditExt* m_nameEdit{nullptr};
    DoubleSpinBox* m_massFlowSpin{nullptr};
    DoubleSpinBox* m_rotationalSpeedSpin{nullptr};
};

#endif // COMPONENTVIEW_H
