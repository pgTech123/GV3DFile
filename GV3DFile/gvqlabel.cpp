/*************************************************************************
 * Project:     GV3D File
 *
 * File Name:   GVQLabel.cpp
 *
 * Author:      Pascal Gendron
 *
 * Version:     0.0.1
 * ************************************************************************/

#include "gvqlabel.h"

GVQLabel::GVQLabel()
{
    /* The Default Image Loaded is at that Location */
    initializeRenderingWidget("./image_test.i3c");
}

GVQLabel::GVQLabel(const char* p_cPath)
{
    /* Load the Image from the Specified Location */
    initializeRenderingWidget(p_cPath);
}

void GVQLabel::initializeRenderingWidget(const char* p_cPath)
{
    /* Creation of the 3D image */
    GV = new GVImage(p_cPath);

    /* Refresh Image Callback */
    refreshTimer = new QTimer(this);
    refreshTimer->start(60);
    connect(refreshTimer,SIGNAL(timeout()),this,SLOT(refreshScreen()));

    /* Frame Initialization */
    frame = new QPixmap();
    frame->fill(Qt::black);

    /* Retrieve Size and Pointer to Data from 3D Model */
    m_intHeight = GV->getHeight();
    m_intWidth = GV->getWidth();
    m_ucharPixels = GV->getData();

    /* Display Initial Frame */
    QLabel::setPixmap(*frame);
}

void GVQLabel::refreshScreen()
{
    /* Image Preparation and Rendering */
    GV->setRotation(PI, 3*PI/2);
    GV->generateImage();

    /* Fit Pixel Map for the Window Resolution */
    QImage img(m_ucharPixels, m_intWidth, m_intHeight, 3*m_intWidth, QImage::Format_RGB888); // 2 pixels width, 2 pixels height, 6 bytes per line, RGB888 format
    QImage scaled = img.scaled(100, 100); // Scale image to show results better
    QPixmap pix = QPixmap::fromImage(scaled); // Create pixmap from image

    /* Set the this Class as the Pixel Map of the Rendered Image */
    QLabel::setPixmap(pix);
}
