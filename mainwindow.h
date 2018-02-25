#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtWidgets>
#include <QSerialPort>
#include <QBitmap>
#include "console.h"
#include "qcustomplot.h"
#include "settingsdialog.h"
#include "quickstateinfo.h"
#include "camplot.h"
#include "decodefsm.h"
#include "camimage.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void about();
    void openSerialPort();
    void closeSerialPort();
    void writeData(const QByteArray &data);
    void readData();

private:
    void createAction();
    void createStatusBar();
    void createDockWindows();

    quickStateInfo *quickInfo;

    camPlot * cameraMain;
    camImage *linescanEvol;

    QMenu *viewMenu;

    decodeFSM *FSM;

    QAction *connectAction;
    QAction *disconnectAction;
    QAction *parameterAction;

    settingsDialog *settingsDiag;
    camPlot *customPlot;
    Console *console;
    QSerialPort *serial;

};

#endif // MAINWINDOW_H
