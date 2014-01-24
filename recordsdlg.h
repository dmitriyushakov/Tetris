#ifndef RECORDSDLG_H
#define RECORDSDLG_H

#include <QDialog>

namespace Ui {
class RecordsDlg;
}

class RecordTable;

class RecordsDlg : public QDialog
{
    Q_OBJECT

public:
    explicit RecordsDlg(QWidget *parent = 0);
    ~RecordsDlg();
    void setRecordTable(RecordTable* tbl);
private:
    RecordTable *table;
    Ui::RecordsDlg *ui;
private slots:
    void showRecords();
};

#endif // RECORDSDLG_H
