#include <QApplication>
#include <QIcon>
#include "gvqlabel.h"

#include <iostream>
#include "gvtests.h"

#define ICON_PATH           "./../GVisionLogo.ico"
#define APPLICATION_NAME    "GV3DFile"

using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //TESTS (REMOVE FOR RELEASE)
        runTestLookupTable();
    //END TESTS

    GVQLabel *l = new GVQLabel();
    QIcon *icon = new QIcon(ICON_PATH);

    l->setGeometry(100,100,720,405);

    l->setWindowTitle(APPLICATION_NAME);
    l->setWindowIcon(*icon);
    l->show();

    return app.exec();
}
