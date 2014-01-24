#include "about.h"
#include "ui_about.h"
#include "version.h"

About::About(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    QLabel *verLbl=ui->versionLbl;
    verLbl->setText(verLbl->text().append(VERSION));
    connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(close()));
    setFixedSize(size());
    setWindowFlags(Qt::Tool);
}

About::~About()
{
    delete ui;
}
