#ifndef GVQLABEL_H
#define GVQLABEL_H

#include <iostream>

#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QTimer>

#include <gvimage.h>

#define PI  3.14159265359

using namespace std;

class GVQLabel : public QLabel
{
    Q_OBJECT
public:
    explicit GVQLabel();

signals:

private slots:
    void refreshScreen();

private:
    QPixmap *frame;
    QTimer *refreshTimer;

    int m_intWidth;
    int m_intHeight;
    unsigned char *m_ucharPixels;

    GVImage *GV;
};

#endif // GVQLABEL_H
