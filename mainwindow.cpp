#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    cameraMain = new camPlot;
    linescanEvol = new camImage(512);
    quickInfo = new quickStateInfo;


    //console = new Console;
    serial = new QSerialPort;

    settingsDiag = new settingsDialog(this);

    createAction();
    createStatusBar();
    createDockWindows();

    setCentralWidget(cameraMain);
    FSM = new decodeFSM;
    FSM->setCam(cameraMain, linescanEvol);
    FSM->setStatePrinter(quickInfo);

    connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);
    connect(console, &Console::getData, this, &MainWindow::writeData);
}

MainWindow::~MainWindow()
{


}

void MainWindow::about()
{
   QMessageBox::about(this, "About Car Link",
            "Ahoj !");
   qDebug() << quickInfo->size();

}

void MainWindow::openSerialPort()
{
    settingsDialog::Settings p = settingsDiag->settings();

    serial->setPortName(p.name);
    serial->setBaudRate(p.baudRate);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite))
    {
        connectAction->setEnabled(false);
        disconnectAction->setEnabled(true);
        parameterAction->setEnabled(false);
        console->setEnabled(true);
        console->setLocalEchoEnabled(false);


    } else {
        QMessageBox::critical(this, "Error", serial->errorString());
    }
}

void MainWindow::closeSerialPort()
{
    if (serial->isOpen())
        serial->close();
    //console->setEnabled(false);
    connectAction->setEnabled(true);
    disconnectAction->setEnabled(false);
    parameterAction->setEnabled(true);
}

void MainWindow::writeData(const QByteArray &data)
{
    serial->write(data);
}

void MainWindow::readData()
{
    QByteArray data = serial->readAll();

    for (int i = 0 ; i < data.size() ; i ++){
        FSM->updateState(data[i]);


        //console->putData(data.toHex().toUpper());
        //console->putData("\x0A");
    }




    /*
    QByteArray data = serial->read(1);

    FSM->updateState(data[0]);


    console->putData(data.toHex().toUpper());
    console->putData("\x0A");
        //double a =  (data[0] & 0x0F) * 256 + ((data[1] & 0xF0)>>4)*16+(data[1] & 0x0F);
        //qDebug() << a;
        //console->putData(a);
    */
}

void MainWindow::createAction()
{
    QMenu *serialMenu = menuBar()->addMenu("Connect");
    QToolBar *serialToolBar = addToolBar("Connect");
    //addToolBar(Qt::LeftToolBarArea, serialToolBar);

    const QIcon connectIcon =  QIcon(":/images/connect.png");
    connectAction = new QAction(connectIcon, "Connect", this);
    connectAction->setStatusTip("Connect to serial port");
    connect(connectAction, &QAction::triggered, this, &MainWindow::openSerialPort);
    serialMenu->addAction(connectAction);
    serialToolBar->addAction(connectAction);

    const QIcon disconnectIcon =  QIcon(":/images/disconnect.png");
    disconnectAction = new QAction(disconnectIcon, "Disconnect", this);
    disconnectAction->setStatusTip("Disconnect the serial port");
    connect(disconnectAction, &QAction::triggered, this, &MainWindow::closeSerialPort);
    serialMenu->addAction(disconnectAction);
    serialToolBar->addAction(disconnectAction);

    const QIcon parameterIcon =  QIcon(":/images/parameter.png");
    parameterAction = new QAction(parameterIcon, "Parameters", this);
    parameterAction->setStatusTip("Serial port selection");
    connect(parameterAction, &QAction::triggered, settingsDiag, &settingsDialog::show);
    serialMenu->addAction(parameterAction);
    serialToolBar->addAction(parameterAction);

    connectAction->setEnabled(true);
    disconnectAction->setEnabled(false);
    parameterAction->setEnabled(true);

    QMenu *helpMenu = menuBar()->addMenu("Help");
    QAction *aboutAct = helpMenu->addAction("About", this, &MainWindow::about);
    aboutAct->setStatusTip("Show the application's About box");

    viewMenu = menuBar()->addMenu("View");

}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Phoenxp >> All");
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock = new QDockWidget("Quick Info", this);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    dock->setWidget(quickInfo);
    addDockWidget(Qt::LeftDockWidgetArea, dock);
    viewMenu->addAction(dock->toggleViewAction());

    /*******************************************************************************************/

    dock = new QDockWidget("Terminal", this);
    console = new Console(dock);

    dock->setWidget(console);
    dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::BottomDockWidgetArea);

    addDockWidget(Qt::LeftDockWidgetArea, dock);

    viewMenu->addAction(dock->toggleViewAction());

    dock = new QDockWidget("Linescan evolution", this);

    dock->setWidget(linescanEvol->imshow());
    dock->setAllowedAreas(Qt::RightDockWidgetArea | Qt::BottomDockWidgetArea);

    addDockWidget(Qt::RightDockWidgetArea, dock);

    viewMenu->addAction(dock->toggleViewAction());


}
