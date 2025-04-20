#ifndef APPLICATIONMODEL_H
#define APPLICATIONMODEL_H

#include <QObject>

namespace nrec {

class ComponentList;
class Component;

} // namespace nrec

class ComponentModel;

class ApplicationModel : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationModel(nrec::ComponentList* components,
                              QObject *parent = nullptr);

    bool addComponent(const QString &name = "");
    bool deleteComponent(ComponentModel* componentModel);
    bool selectComponent(ComponentModel* componentModel);

    void initialize();

signals:
    void componentAdded(ComponentModel* componentModel);
    void componentDeleted(ComponentModel* componentModel);
    void componentSelected(ComponentModel* componentModel);

private:
    QVector<ComponentModel*> m_componentModels;
    nrec::ComponentList* m_components{nullptr};
    int m_totalComponentsCount{0};
};

#endif // APPLICATIONMODEL_H
