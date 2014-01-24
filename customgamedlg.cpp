#include "customgamedlg.h"
#include "ui_customgamedlg.h"
#include "gameproperties.h"

CustomGameDlg::CustomGameDlg(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CustomGameDlg)
{
    ui->setupUi(this);
    connect(ui->startBtn,SIGNAL(clicked()),this,SLOT(onStart()));
    connect(ui->cancelBtn,SIGNAL(clicked()),this,SLOT(close()));
    connect(ui->heightSpin,SIGNAL(valueChanged(int)),this,SLOT(heightChanged()));
    connect(ui->complicationCheck,SIGNAL(toggled(bool)),this,SLOT(complicationTrigerred()));
    setWindowFlags(Qt::Tool);
    setFixedSize(size());
    ui->startBtn->setFocus();
}

void CustomGameDlg::complicationTrigerred(){
    ui->accelerationSlider->setEnabled(ui->complicationCheck->isChecked());
}

void CustomGameDlg::heightChanged(){
    ui->fillingSpin->setMaximum(ui->heightSpin->value()/2);
}

void CustomGameDlg::onStart(){
    GameProperties prop;
    prop.setSize(
                ui->widthSpin->value(),
                ui->heightSpin->value());
    prop.setFilling(ui->fillingSpin->value());
    prop.setInterval(ui->intervalSpin->value()*1000);
    prop.setComplication(ui->complicationCheck->isChecked());
    prop.setAccelerationVar(210-ui->accelerationSlider->value());

    emit startNewGame(prop);

    close();
}

CustomGameDlg::~CustomGameDlg()
{
    delete ui;
}
