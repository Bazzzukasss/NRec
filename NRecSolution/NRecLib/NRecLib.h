#ifndef NRECLIB_H
#define NRECLIB_H

#include <string>
#include <vector>
#include <memory>

namespace nrec {

class Component {
public:
    Component(const std::string& name);

    std::string name () const;
    double massFlow () const;
    double rotationalSpeed () const;

    void setName (const std::string& name);
    void setMassFlow (const double& massFlow);
    void setRotationalSpeed(const double& rotationalSpeed);

private:
    std::string m_name{""};
    double m_massFlow{0.0};
    double m_rotationalSpeed{0.0};
};

class ComponentList {
public:
    ComponentList() = default;

    size_t numberOfComponents() const;
    Component* getComponent (const int number) const;
    Component* getComponent (const std::string& name) const;

    bool addComponent (const std::string& name);
    bool deleteComponent (const std::string& name);

private:
    std::vector<std::shared_ptr<Component>> m_components;
};

} // namespace nrec

#endif // NRECLIB_H
