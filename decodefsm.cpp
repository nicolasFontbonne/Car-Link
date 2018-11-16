#include "decodefsm.h"

decodeFSM::decodeFSM() : deadBeefState(0), state(INIT), LinescanCounter(0), LinescanValue(0), Linescan(NB_PX)
{
    servoCtrl = new float;
    encoderRight = new unsigned int;
}

void decodeFSM::setCam(camPlot *plot, camImage *image)
{
    LinescanPlot = plot;
    LinescanImage = image;

}

void decodeFSM::setStatePrinter(quickStateInfo *quickStateInfo)
{
    quickState = quickStateInfo;
}
void decodeFSM::updateState(char byte)
{
    deadBeefDetector(byte);
    if (deadBeefState == 4){
        state = INIT;
    }
    switch (state) {
    case INIT:
        LinescanCounter = 0;
        deadBeefState = 0;
        state = LINESCAN;
        LinescanValue = 0;
        floatCounter = 0;
        motorCounter = 0;
        break;

    case LINESCAN:

        if (LinescanCounter % 2 == 0){
            LinescanValue = ((byte & 0xF0)>>4)*16+(byte & 0x0F);;
        }
        else{
            LinescanValue += (byte & 0x0F) * 256 ;
            Linescan[LinescanCounter/2] = LinescanValue;

        }
        LinescanCounter += 1;
        if (LinescanCounter >= 2*(NB_PX)){
            LinescanCounter = 0;
            LinescanValue = 0;
            state = SERVO;
            LinescanPlot->update(Linescan);
            LinescanImage->update(Linescan);
            //qDebug() << Linescan;
        }

        break;

    case SERVO:
        floatBuffer[floatCounter++] = byte;
        //qDebug() << byte;

        if (floatCounter == 4){
            memcpy(servoCtrl, floatBuffer, 4);
            //qDebug() << *servoCtrl;
            floatCounter = 0;
            quickState->updateServo(*servoCtrl);
            state = ENCODER_RIGHT;

        }

        break;

    case ENCODER_RIGHT:
        floatBuffer[floatCounter++] = byte;
        //qDebug() << byte;
        if (floatCounter == 4){
            memcpy(encoderRight, floatBuffer, 4);
            floatCounter = 0;
            quickState->updateEncoRight(*encoderRight);
        }
        break;

    default:
        break;
    }
}

void decodeFSM::deadBeefDetector(char byte)
{
    if (deadBeefState == 0 && (byte == (char)0xDE))
    {
        deadBeefState += 1;
    }
    else if (deadBeefState == 1 && byte == (char)0xAD)
    {
        deadBeefState += 1;
    }
    else if (deadBeefState == 2 && byte == (char)0xBE)
    {
        deadBeefState += 1;
    }
    else if (deadBeefState == 3 && byte == (char)0xEF)
    {
        deadBeefState += 1;
    }
    else {
        deadBeefState = 0;
    }
}
