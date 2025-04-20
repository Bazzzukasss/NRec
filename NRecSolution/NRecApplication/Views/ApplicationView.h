#ifndef APPLICATIONVIEW_H
#define APPLICATIONVIEW_H

#include <QMainWindow>

class ApplicationViewModel;
class ComponentViewModel;
class QListView;

class ApplicationView : public QMainWindow
{
    Q_OBJECT
public:
    explicit ApplicationView(ApplicationViewModel* applicationViewModel,
                             QWidget *parent = nullptr);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    void setSelectedComponent(ComponentViewModel *componentViewModel);
    void onCurrentItemChanged(const QModelIndex &index) const;
    void onAddButtonClicked() const;
    void onDelButtonClicked() const;

private:
    ApplicationViewModel* m_applicationViewModel{nullptr};
    QListView* m_listView{nullptr};
};

#endif // APPLICATIONVIEW_H
