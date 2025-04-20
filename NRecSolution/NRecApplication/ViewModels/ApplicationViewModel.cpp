#include "ApplicationViewModel.h"
#include "Models/ApplicationModel.h"
#include "Models/ComponentListModel.h"
#include "ViewModels/ComponentViewModel.h"

ApplicationViewModel::ApplicationViewModel(ApplicationModel* applicationModel,
                                           QObject *parent)
    : QObject{parent},  m_applicationModel{applicationModel}
{
    m_componentListModel = new ComponentListModel(this);

    connect(applicationModel, &ApplicationModel::componentAdded,
            this, &ApplicationViewModel::onComponentAdded);
    connect(applicationModel, &ApplicationModel::componentDeleted,
            this, &ApplicationViewModel::onComponentDeleted);
    connect(applicationModel, &ApplicationModel::componentSelected,
            this, &ApplicationViewModel::onComponentSelected);
}

void ApplicationViewModel::addComponentRequest(const QString &name)
{
    m_applicationModel->addComponent(name);
}

void ApplicationViewModel::deleteComponentRequest(const QVector<int> numbers)
{
    for(const auto& number : numbers)
    {
        if(auto componentModel = m_componentListModel->getComponent(number))
        {
            m_applicationModel->deleteComponent(componentModel);
        }
    }
}

void ApplicationViewModel::selectComponentRequest(const int number)
{
    auto componentModel = m_componentListModel->getComponent(number);
    m_applicationModel->selectComponent(componentModel);
}

ComponentListModel* ApplicationViewModel::getComponentListModel() const
{
    return m_componentListModel;
}

ComponentViewModel* ApplicationViewModel::getSelectedComponent() const
{
    return m_selectedComponent;
}

void ApplicationViewModel::setSelectedComponent(ComponentViewModel *component)
{
    if (m_selectedComponent != component)
    {
        m_selectedComponent = component;

        emit selectedComponentChanged(component);
    }
}

void ApplicationViewModel::onComponentAdded(ComponentModel* componentModel)
{
    m_componentListModel->addComponent(componentModel);
}

void ApplicationViewModel::onComponentDeleted(ComponentModel* componentModel)
{
    m_componentListModel->deleteComponent(componentModel);
}

void ApplicationViewModel::onComponentSelected(ComponentModel* componentModel)
{
    if (m_selectedComponent)
    {
        m_selectedComponent->deleteLater();
    }

    auto componentViewModel = new ComponentViewModel(componentModel, this);
    setSelectedComponent(componentViewModel);
}
