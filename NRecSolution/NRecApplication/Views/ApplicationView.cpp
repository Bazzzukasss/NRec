#include "ApplicationView.h"
#include "ViewModels/ApplicationViewModel.h"
#include "Views/ComponentView.h"
#include "Models/ComponentListModel.h"

#include <QApplication>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QItemSelectionModel>
#include <QPushbutton>
#include <QKeyEvent>

ApplicationView::ApplicationView(ApplicationViewModel *applicationViewModel,
                                 QWidget *parent)
    : QMainWindow{parent}, m_applicationViewModel{applicationViewModel}
{
    auto centralWidget = new QWidget(this);

    auto addButton = new QPushButton(tr("Add Component"), this);
    auto delButton = new QPushButton(tr("Delete Component"), this);

    m_listView = new QListView(this);
    m_listView->setModel(applicationViewModel->getComponentListModel());
    m_listView->setSelectionMode(QAbstractItemView::SelectionMode::ExtendedSelection);

    auto vLayout = new QVBoxLayout();
    vLayout->addWidget(addButton);
    vLayout->addWidget(delButton);
    vLayout->addWidget(m_listView);

    auto hLayout = new QHBoxLayout();
    hLayout->addLayout(vLayout);
    hLayout->addStretch();

    centralWidget->setLayout(hLayout);
    setCentralWidget(centralWidget);

    connect(applicationViewModel, &ApplicationViewModel::selectedComponentChanged,
            this, &ApplicationView::setSelectedComponent);

    connect(m_listView, &QListView::clicked,
            this, &ApplicationView::onCurrentItemChanged);
    connect(addButton, &QPushButton::clicked,
            this, &ApplicationView::onAddButtonClicked);
    connect(delButton, &QPushButton::clicked,
            this, &ApplicationView::onDelButtonClicked);
}

void ApplicationView::setSelectedComponent(ComponentViewModel *componentViewModel)
{
    auto componentView = new ComponentView(componentViewModel, this);

    componentView->exec();
}

void ApplicationView::onCurrentItemChanged(const QModelIndex &index) const
{
    if (QApplication::keyboardModifiers() == Qt::NoModifier)
    {
        m_applicationViewModel->selectComponentRequest(index.row());
    }
}

void ApplicationView::onAddButtonClicked() const
{
    m_applicationViewModel->addComponentRequest();
}

void ApplicationView::onDelButtonClicked() const
{
    QVector<int> numbers;

    for (const auto& index : m_listView->selectionModel()->selectedIndexes())
    {
        numbers.push_back(index.row());
    }

    m_applicationViewModel->deleteComponentRequest(numbers);
}

void ApplicationView::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        onDelButtonClicked();
    }

    QWidget::keyPressEvent(event);
}
