#ifndef COMPONENTVIEWMODEL_H
#define COMPONENTVIEWMODEL_H

#include <QObject>

#include "Models/ComponentModel.h"

class ComponentViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ComponentViewModel(ComponentModel* componentModel,
                                QObject *parent = nullptr);

    QString getName() const;
    double getMassFlow() const;
    double getRotationalSpeed() const;

    void setName(const QString& name);
    void setMassFlow(const double& massFlow);
    void setRotationalSpeed(const double& rotationalSpeed);

signals:
    void nameChanged(const QString& name);
    void massFlowChanged(const double& massFlow);
    void rotationalSpeedChanged(const double& rotationalSpeed);

private:
    ComponentModel* m_componentModel{nullptr};
    QString m_name{""};
    double m_massFlow{0.0};
    double m_rotationalSpeed{0.0};
};

#endif // COMPONENTVIEWMODEL_H
