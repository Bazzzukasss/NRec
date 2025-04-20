#ifndef APPLICATIONVIEWMODEL_H
#define APPLICATIONVIEWMODEL_H

#include <QObject>
#include <QStringList>

class ApplicationModel;
class ComponentModel;
class ComponentViewModel;
class ComponentListModel;

class ApplicationViewModel : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationViewModel(ApplicationModel* applicationModel,
                                  QObject *parent = nullptr);

    void addComponentRequest(const QString& name = "");
    void deleteComponentRequest(const QVector<int> numbers);
    void selectComponentRequest(const int number);

    ComponentListModel* getComponentListModel() const;
    ComponentViewModel* getSelectedComponent() const;

signals:
    void selectedComponentChanged(ComponentViewModel* componentViewModel);

private:
    void onComponentAdded(ComponentModel* componentModel);
    void onComponentDeleted(ComponentModel* componentModel);
    void onComponentSelected(ComponentModel* componentModel);

    void setSelectedComponent(ComponentViewModel* component);

private:
    ComponentListModel* m_componentListModel{nullptr};
    ComponentViewModel* m_selectedComponent{nullptr};
    ApplicationModel* m_applicationModel{nullptr};
};

#endif // APPLICATIONVIEWMODEL_H
