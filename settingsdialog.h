#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include <QtSerialPort/QSerialPort>
#include <QSerialPortInfo>

#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QComboBox>
#include <QPushButton>
#include <QDebug>

class settingsDialog : public QDialog
{
    Q_OBJECT
public:
    struct Settings {
            QString name;
            qint32 baudRate;
        };

    explicit settingsDialog(QWidget *parent = nullptr);
    ~settingsDialog();

    Settings settings() const;

private slots:
    void apply();
    void rescan();

private:
    void fillPortsParameters();
    void fillPortsInfo();
    void updateSettings();

    QComboBox *baudRateBox;
    QComboBox *serialPortList;


private:
    Settings currentSettings;
};

#endif // SETTINGSDIALOG_H
