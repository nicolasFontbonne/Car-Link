#include "quickstateinfo.h"

quickStateInfo::quickStateInfo(QWidget *parent) :
    QWidget(parent)
{
    QFormLayout *formLayout = new QFormLayout;
    servoCmd = new QLineEdit; servoCmd->setReadOnly(true);
    rightMotorCmd = new QLineEdit; rightMotorCmd->setReadOnly(true);
    leftMotorCmd = new QLineEdit; leftMotorCmd->setReadOnly(true);
    leftEncoderPeriod = new QLineEdit; leftEncoderPeriod->setReadOnly(true);
    rightEncoderPeriod = new QLineEdit; rightEncoderPeriod->setReadOnly(true);


    servoCmd->insert(QString::number(0.0));
    rightMotorCmd->insert(QString::number(0.0));
    leftMotorCmd->insert(QString::number(0.0));
    leftEncoderPeriod->insert(QString::number(0));
    rightEncoderPeriod->insert(QString::number(0));

    formLayout->addRow("Servo-motor", servoCmd);
    formLayout->addRow("Left Motor", leftMotorCmd);
    formLayout->addRow("Left Encoder Period", leftEncoderPeriod);
    formLayout->addRow("Right Motor", rightMotorCmd);
    formLayout->addRow("Right Encoder Period", rightEncoderPeriod);

    setLayout(formLayout);

}
