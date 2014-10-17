#include "gvqlabel.h"

GVQLabel::GVQLabel()
{
    GV = new GVImage("./../test.txt");

    //Refresh Image Timer Settings
    refreshTimer = new QTimer(this);
    refreshTimer->start(60);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(refreshScreen()));

    //Frame Initialisation
    frame = new QPixmap();
    frame->fill(Qt::black);

    m_intHeight = GV->getHeight();
    m_intWidth = GV->getWidth();
    m_ucharPixels = GV->getData();

    //Display Initial Frame
    QLabel::setPixmap(*frame);

}


void GVQLabel::refreshScreen()
{
    GV->setRotation(PI, 3*PI/2);
    GV->generateImage();

    QImage img(m_ucharPixels, m_intWidth, m_intHeight, 3*m_intWidth, QImage::Format_RGB888); // 2 pixels width, 2 pixels height, 6 bytes per line, RGB888 format
    QImage scaled = img.scaled(100, 100); // Scale image to show results better
    QPixmap pix = QPixmap::fromImage(scaled); // Create pixmap from image

    QLabel::setPixmap(pix);
}
