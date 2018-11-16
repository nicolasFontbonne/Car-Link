#ifndef DECODEFSM_H
#define DECODEFSM_H

#include <QVector>
#include <QDebug>
#include "camplot.h"
#include "camimage.h"
#include "quickstateinfo.h"
#include <cstring>



#define NB_PX 128

class decodeFSM
{
public:
    decodeFSM();
    void setCam(camPlot *plot, camImage *image);
    void setStatePrinter(quickStateInfo *quickStateInfo);
    void updateState(char byte);


private:
    void deadBeefDetector(char byte);
    unsigned int deadBeefState;

    enum decodeState {
        INIT,
        LINESCAN,
        SERVO,
        ENCODER_RIGHT,
        MOTOR
    };

    decodeState state;
    char floatBuffer[4];
    unsigned int floatCounter;

    unsigned int LinescanCounter;
    double LinescanValue;
    QVector<double> Linescan;



    float *servoCtrl;
    unsigned int *encoderRight;



    unsigned int motorCounter;


    camPlot *LinescanPlot;
    camImage *LinescanImage;
    quickStateInfo *quickState;

};

#endif // DECODEFSM_H
