#ifndef CAMIMAGE_H
#define CAMIMAGE_H
#include <QImage>
#include <QBitmap>
#include <QLabel>
#include <QPixmap>
#include <QWidget>
#include <QVector>
#include <QDebug>

class camImage
{
public:
    camImage(int height);
    void update(QVector<double> Linescan);
    QLabel *imshow();

private:
    int m_height;
    QImage *imageData;
    QPixmap *imageShow;
    QLabel *label;

    QColor colorFromDouble(double value);

};

#endif // CAMIMAGE_H
