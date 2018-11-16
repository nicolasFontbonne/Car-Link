#include "camimage.h"

camImage::camImage(int height)
{
    m_height = height;
    imageData = new QImage(128, height,  QImage::Format_Grayscale8);
    for (int i = 0; i < 128 ; i++){
        for (int j = 0 ; j < height ; j++){
            imageData->setPixelColor(i, j,  QColor(200, 200, 200));
        }
    }
    label = new QLabel;
}

void camImage::update(QVector<double> Linescan)
{
    for (int i = 0 ; i < 128 ; i++){
        for (int j = m_height-1 ; j > 0 ; j--){
            imageData->setPixelColor(i, j,  imageData->pixelColor(i, j-1));
        }
        imageData->setPixelColor(i, 0,  colorFromDouble( Linescan[i]));
    }
    label->setPixmap(QPixmap::fromImage(*imageData));


}

QLabel *camImage::imshow()
{
    label->setPixmap(QPixmap::fromImage(*imageData));
    return label;
}

QColor camImage::colorFromDouble(double value)
{
    uint val = value/4096*255;
    return QColor(val, val, val);
}
