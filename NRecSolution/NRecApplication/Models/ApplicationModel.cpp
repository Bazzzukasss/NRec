#include "ApplicationModel.h"
#include "ComponentModel.h"
#include "NRecLib.h"

const QString DefaultComponentName{"Component"};

ApplicationModel::ApplicationModel(nrec::ComponentList* components,
                                   QObject *parent)
    : QObject{parent}, m_components{components}
{
}

bool ApplicationModel::addComponent(const QString &name)
{
    std::string componentName{name.toStdString()};
    m_totalComponentsCount++;
    if (componentName.empty())
    {
        componentName = QString("%1_%2")
                            .arg(DefaultComponentName)
                            .arg(m_totalComponentsCount).toStdString();
    }

    auto isAdded = m_components->addComponent(componentName);
    if (isAdded)
    {
        auto component = m_components->getComponent(componentName);
        auto componentModel = new ComponentModel(component, this);
        m_componentModels.push_back(componentModel);

        emit componentAdded(componentModel);
    }

    return isAdded;
}

bool ApplicationModel::deleteComponent(ComponentModel* componentModel)
{
    auto isDeleted = m_components->deleteComponent(componentModel->getName());

    if (isDeleted)
    {
        emit componentDeleted(componentModel);

        m_componentModels.removeOne(componentModel);
        componentModel->deleteLater();
    }

    return isDeleted;
}

bool ApplicationModel::selectComponent(ComponentModel *componentModel)
{
    emit componentSelected(componentModel);

    return true;
}

void ApplicationModel::initialize()
{
    for(int i = 0; i < m_components->numberOfComponents(); ++i)
    {
        if (auto component = m_components->getComponent(i))
        {
            auto componentModel = new ComponentModel(component, this);
            m_componentModels.push_back(componentModel);

            emit componentAdded(componentModel);
        }
    }
}
