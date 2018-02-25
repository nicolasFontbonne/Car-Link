#ifndef DECODEFSM_H
#define DECODEFSM_H

#include <QVector>
#include <QDebug>
#include "camPlot.h"
#include "camimage.h"


#define NB_PX 128

class decodeFSM
{
public:
    decodeFSM();
    void setCam(camPlot *plot, camImage *image);
    void updateState(char byte);


private:
    void deadBeefDetector(char byte);
    unsigned int deadBeefState;

    enum decodeState {
        INIT,
        LINESCAN,
        SERVO,
        MOTOR
    };

    decodeState state;
    unsigned int LinescanCounter;
    double LinescanValue;
    QVector<double> Linescan;


    camPlot *LinescanPlot;
    camImage *LinescanImage;

};

#endif // DECODEFSM_H
