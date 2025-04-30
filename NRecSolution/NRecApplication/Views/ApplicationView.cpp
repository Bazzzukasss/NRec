#include "ApplicationView.h"
#include "ViewModels/ApplicationViewModel.h"
#include "Views/ComponentView.h"
#include "Views/CustomWidgets.h"
#include "Models/ComponentListModel.h"

#include <QApplication>
#include <QListView>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QItemSelectionModel>
#include <QKeyEvent>

ApplicationView::ApplicationView(ApplicationViewModel *applicationViewModel,
                                 QWidget *parent)
    : QMainWindow{parent}, m_applicationViewModel{applicationViewModel}
{
    setWindowTitle(tr("NREC POC Application"));

    auto centralWidget = new QWidget(this);
    auto addButton = new PushButton(tr("Add Component"), this);
    addButton->setPriority(Priority::Primary);
    addButton->setSizeScale(SizeScale::Medium);

    auto delButton = new PushButton(tr("Delete Component"), this);
    delButton->setPriority(Priority::Secondary);
    delButton->setSizeScale(SizeScale::Medium);

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

    componentView->resize(200, 200);
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
