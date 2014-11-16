/*************************************************************************
 * Project:     GV3D File
 *
 * File Name:   GVQLabel.h
 *
 * Author:      Pascal Gendron
 *
 * Version:     0.0.1
 * ************************************************************************/

#ifndef GVQLABEL_H
#define GVQLABEL_H

#include <QLabel>
#include <QPixmap>
#include <QImage>
#include <QTimer>
#include "gvimage.h"
#include "gvlookuptable.h"

/*************************************************************************
 * GVQLabel Class:
 *
 * The purpose of this class is to provide a graphic layout to display the
 * image rendered.
 *************************************************************************/

class GVQLabel : public QLabel
{
    Q_OBJECT

public:
    explicit GVQLabel();
    GVQLabel(const char* c_p_Path);

private:
    void initializeRenderingWidget(const char* c_p_Path);

private slots:
    void refreshScreen();

private:
    /* Qt Grapical Window & Screen Refresh Timer */
    QPixmap *frame;
    QTimer *refreshTimer;

    /* 2D Image (Rendered) */
    int m_intWidth;
    int m_intHeight;
    unsigned char *m_ucharPixels;

    /* 3D Image */
    GVImage *GV;
};

#endif // GVQLABEL_H
