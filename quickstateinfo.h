#ifndef QUICKSTATEINFO_H
#define QUICKSTATEINFO_H

#include <QWidget>
#include <QLineEdit>
#include <QFormLayout>


class quickStateInfo : public QWidget
{
public:
    quickStateInfo(QWidget *parent = 0);
    void updateStateInfo(qreal servoCmd, qreal rightMotorCmd, qreal leftMotorCmd, qint32 encoderPeriod);
    void updateServo(qreal servoCtrl);
    void updateEncoRight(unsigned int encoderRight);

private:
    QLineEdit *servoCmd;
    QLineEdit *rightMotorCmd;
    QLineEdit *leftMotorCmd;

    QLineEdit *leftEncoderPeriod;
    QLineEdit *rightEncoderPeriod;
};

#endif // QUICKSTATEINFO_H
