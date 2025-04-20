#include "ComponentListModel.h"
#include "Models/ComponentModel.h"

ComponentListModel::ComponentListModel(QObject *parent)
    : QAbstractItemModel(parent)
{
}

void ComponentListModel::addComponent(ComponentModel *componentModel)
{
    beginResetModel();
    m_componentModels.push_back(componentModel);
    connect(componentModel, &ComponentModel::nameChanged,
            this, [&](){ dataChanged({},{}); });
    endResetModel();
}

void ComponentListModel::deleteComponent(ComponentModel *componentModel)
{
    beginResetModel();
    m_componentModels.removeOne(componentModel);
    endResetModel();
}

ComponentModel* ComponentListModel::getComponent(const int number)
{
    return number < m_componentModels.size() ? m_componentModels.at(number)
                                             : nullptr;
}

int ComponentListModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_componentModels.size();
}

int ComponentListModel::columnCount(const QModelIndex &parent) const
{
    return 1;
}

QVariant ComponentListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
    {
        return QVariant();
    }

    if (role == Qt::DisplayRole)
    {
        if (index.column() == 0)
        {
            const auto& componentModel = m_componentModels[index.row()];
            return QString::fromStdString(componentModel->getName());
        }
    }
    return QVariant();
}

QModelIndex ComponentListModel::index(int row, int column, const QModelIndex &parent) const
{
    if (!hasIndex(row, column, parent) || parent.isValid())
    {
        return QModelIndex();
    }

    return createIndex(row, column);
}

QModelIndex ComponentListModel::parent(const QModelIndex &index) const
{
    return QModelIndex();
}
