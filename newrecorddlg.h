#ifndef NEWRECORDDLG_H
#define NEWRECORDDLG_H

#include <QDialog>

#include "record.h"

namespace Ui {
class NewRecordDlg;
}

class NewRecordDlg : public QDialog
{
    Q_OBJECT
private:
    int confWidth;
    int confHeight;
    int confScore;
public:
    explicit NewRecordDlg(QWidget *parent = 0);
    ~NewRecordDlg();
    void setConfigs(int score,int width,int height);
protected:
    void closeEvent(QCloseEvent *ev);
signals:
    void accept(Record record);
    void cancel();
private slots:
    void acceptClicked();
    void cancelClicked();
private:
    Ui::NewRecordDlg *ui;
};

#endif // NEWRECORDDLG_H
