#include "settingsdialog.h"

settingsDialog::settingsDialog(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *verticalLayout = new QVBoxLayout;

    QGroupBox *selectBox = new QGroupBox("Port");
    QHBoxLayout *selectLayout = new QHBoxLayout;
    serialPortList = new QComboBox();
    serialPortList->clear();

    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if (info.portName().contains("tty"))
        {
            serialPortList->addItem(info.portName());
        }
    }
    selectLayout->addWidget(serialPortList);
    selectBox->setLayout(selectLayout);

    QGroupBox *parametersBox = new QGroupBox("Parameters");
    QHBoxLayout *parametersLayout = new QHBoxLayout;
    QLabel *baudRateLabel = new QLabel("Baud rate");
    baudRateBox = new QComboBox();
    baudRateBox->addItem(QStringLiteral("9600"), QSerialPort::Baud9600);
    baudRateBox->addItem(QStringLiteral("19200"), QSerialPort::Baud19200);
    baudRateBox->addItem(QStringLiteral("38400"), QSerialPort::Baud38400);
    baudRateBox->addItem(QStringLiteral("115200"), QSerialPort::Baud115200);
    parametersLayout->addWidget(baudRateLabel);
    parametersLayout->addWidget(baudRateBox);
    parametersBox->setLayout(parametersLayout);

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    //QSpacerItem *horizontalSpacer = new QSpacerItem(96, 20, QSizePolicy::Expanding);
    QPushButton *rescanButton = new QPushButton("Re-scan");
    connect(rescanButton, &QPushButton::clicked, this, &settingsDialog::rescan);
    QPushButton *applyButton = new QPushButton("Ok");
    applyButton->setDefault(true);
    connect(applyButton, &QPushButton::clicked, this, &settingsDialog::apply);
    horizontalLayout->addWidget(rescanButton);
    //horizontalLayout->addItem(horizontalSpacer);
    horizontalLayout->addWidget(applyButton);

    verticalLayout->addWidget(selectBox);
    verticalLayout->addWidget(parametersBox);
    verticalLayout->addLayout(horizontalLayout);

    setLayout(verticalLayout);
    setFixedSize(290, 210);

}

settingsDialog::~settingsDialog()
{

}

settingsDialog::Settings settingsDialog::settings() const
{
    return currentSettings;
}

void settingsDialog::apply()
{
    updateSettings();
    hide();
}

void settingsDialog::rescan()
{
    serialPortList->clear();
    const auto infos = QSerialPortInfo::availablePorts();
    for (const QSerialPortInfo &info : infos)
    {
        if (info.portName().contains("tty"))
        {
            serialPortList->addItem(info.portName());
        }
    }
}

void settingsDialog::updateSettings()
{
    currentSettings.name = serialPortList->currentText();
    currentSettings.baudRate = static_cast<QSerialPort::BaudRate>(
                baudRateBox->itemData(baudRateBox->currentIndex()).toInt());
}
