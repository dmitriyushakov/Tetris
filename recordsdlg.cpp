#include <QTableWidgetItem>

#include "recordsdlg.h"
#include "ui_recordsdlg.h"
#include "recordtable.h"
#include "record.h"

RecordsDlg::RecordsDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RecordsDlg)
{
    table=0;

    ui->setupUi(this);
    setFixedSize(size());

    QStringList tableHeaders;
    tableHeaders.append(tr("Player"));
    tableHeaders.append(tr("Score"));
    ui->tableWidget->setHorizontalHeaderLabels(tableHeaders);
    ui->tableWidget->setColumnWidth(0,150);
    ui->tableWidget->setColumnWidth(1,150);

    ui->comboBox->addItem("5x10",QVariant(5));
    ui->comboBox->addItem("10x20",QVariant(10));
    ui->comboBox->addItem("15x30",QVariant(15));
    ui->comboBox->addItem("20x40",QVariant(20));

    connect(ui->comboBox,SIGNAL(currentIndexChanged(int)),this,SLOT(showRecords()));
    connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(close()));
}

RecordsDlg::~RecordsDlg()
{
    delete ui;
}

void RecordsDlg::setRecordTable(RecordTable *tbl){
    table=tbl;
    showRecords();
}

void RecordsDlg::showRecords(){
    if(table!=0){
        int width=ui->comboBox->itemData(ui->comboBox->currentIndex()).toInt();
        int height=width*2;
        int count=table->count(width,height);
        ui->tableWidget->clearContents();
        ui->tableWidget->setRowCount(count);

        Record **records=(Record**)malloc(sizeof(Record*)*count);
        for(int i=0;i<count;i++){
            records[i]=table->get(i,width,height);
        }

        for(int i=0;i<count-1;i++){
            int maxScore=records[i]->score();
            int maxIndex=i;
            for(int j=i;j<count;j++){
                if(records[j]->score()>maxScore){
                    maxScore=records[j]->score();
                    maxIndex=j;
                }
            }
            if(maxIndex!=i){
                Record *t=records[i];
                records[i]=records[maxIndex];
                records[maxIndex]=t;
            }
        }

        for(int i=0;i<count;i++){
            Record *record=records[i];
            QTableWidgetItem *playerItem=new QTableWidgetItem(record->player());
            QTableWidgetItem *scoreItem=new QTableWidgetItem(QString::number(record->score()));
            ui->tableWidget->setItem(i,0,playerItem);
            ui->tableWidget->setItem(i,1,scoreItem);
        }
        free(records);
    }
}
