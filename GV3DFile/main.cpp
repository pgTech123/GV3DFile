#include <QApplication>
#include <QIcon>
#include "gvqlabel.h"

#include <iostream>
#include "gvbinaryfunctions.h"
using namespace std;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    //TEST
    /*double arrTest[8] = {-28,1,6.9,3,4,5,7,-6.2};
    unsigned char indexTest[8];

    sort(arrTest, indexTest);

    cout << "Array Sort Test" << endl;
    for(int i = 0 ; i < 8; i++)
    {
        cout << (int)indexTest[i] << endl;
    }
    cout << "End Test" << endl;*/

    //END TEST


    GVQLabel *l = new GVQLabel();
    QIcon *icon = new QIcon("C:\\Users\\Pascal\\Documents\\GV\\Logos\\GVisionLogo.ico");

    l->setGeometry(100,100,720,405);

    l->setWindowTitle("GV3DFile");
    l->setWindowIcon(*icon);
    l->show();

    return app.exec();
}
