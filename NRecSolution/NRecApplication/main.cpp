#include "Models/ApplicationModel.h"
#include "ViewModels/ApplicationViewModel.h"
#include "Views/ApplicationView.h"
#include "NRecLib.h"

#include <QApplication>
#include <QFile>

QString loadStyleSheet(const QString &file)
{
    QString styleSheet;
    QFile styleFile(file);

    if (styleFile.exists())
    {
        styleFile.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&styleFile);

        styleSheet += ts.readAll();
    }

    return styleSheet;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    nrec::ComponentList componentList;
    ApplicationModel model(&componentList);
    ApplicationViewModel viewModel(&model);
    ApplicationView view(&viewModel);
    auto stylesheet = loadStyleSheet("://Resources/Styles/Application.qss");

    view.setMinimumSize({800, 600});
    view.setStyleSheet(stylesheet);
    view.show();

    app.exec();
}
