#include <QCloseEvent>

#include "newrecorddlg.h"
#include "ui_newrecorddlg.h"

NewRecordDlg::NewRecordDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NewRecordDlg)
{
    confWidth=0;
    confHeight=0;
    confScore=0;
    ui->setupUi(this);
    setFixedSize(size());
    connect(ui->buttonBox,SIGNAL(accepted()),this,SLOT(acceptClicked()));
    connect(ui->buttonBox,SIGNAL(rejected()),this,SLOT(cancelClicked()));
}

NewRecordDlg::~NewRecordDlg()
{
    delete ui;
}

void NewRecordDlg::setConfigs(int score, int width, int height){
    confScore=score;
    confHeight=height;
    confWidth=width;
}

void NewRecordDlg::closeEvent(QCloseEvent *ev){
    if(ev->spontaneous())emit cancel();
    ev->accept();
}

void NewRecordDlg::acceptClicked(){
    Record record(ui->nameEdit->text(),confScore,confWidth,confHeight);
    emit accept(record);
    close();
}

void NewRecordDlg::cancelClicked(){
    emit cancel();
    close();
}
