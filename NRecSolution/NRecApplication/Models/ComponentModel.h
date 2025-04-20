#ifndef COMPONENTMODEL_H
#define COMPONENTMODEL_H

#include <QObject>

namespace nrec {

class Component;

} //namespace nrec

class ComponentModel : public QObject
{
    Q_OBJECT
public:
    explicit ComponentModel(nrec::Component* component,
                            QObject *parent = nullptr);

    std::string getName () const;
    double getMassFlow () const;
    double getRotationalSpeed () const;

    void setName (const std::string& name);
    void setMassFlow (const double& massFlow);
    void setRotationalSpeed(const double& rotationalSpeed);

signals:
    void nameChanged (const QString& name);
    void massFlowChanged (const double& massFlow);
    void rotationalSpeedChanged(const double& rotationalSpeed);

private:
    nrec::Component* m_component{nullptr};
};

#endif // COMPONENTMODEL_H
