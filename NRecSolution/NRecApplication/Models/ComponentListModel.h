#ifndef COMPONENTLISTMODEL_H
#define COMPONENTLISTMODEL_H

#include <QAbstractListModel>

class ComponentModel;

class ComponentListModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    ComponentListModel(QObject* parent = nullptr);

    void addComponent(ComponentModel* componentModel);
    void deleteComponent(ComponentModel* componentModel);
    ComponentModel* getComponent(const int number);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &index) const override;

private:
    QList<ComponentModel*> m_componentModels;
};

#endif // COMPONENTLISTMODEL_H
