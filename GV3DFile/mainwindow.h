#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "gvqlabel.h"

#include <iostream>

/* Default 3D Image Path */
#define DEFAULT_FILE_PATH           "./../TestCube3D3Levels.i3c"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void incrementRotation();

    void setAngleX(int value);
    void setAngleY(int value);
    void on_pushButtonStart_clicked();

private:
    Ui::MainWindow *ui;
    GVQLabel *renderingWidget;
    QTimer *AutorotateTimer;

    bool m_bRotationAuto;

    double m_dAngleX;
    double m_dAngleY;
};

#endif // MAINWINDOW_H
