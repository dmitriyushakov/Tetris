#ifndef CUSTOMGAMEDLG_H
#define CUSTOMGAMEDLG_H

#include <QWidget>

namespace Ui {
class CustomGameDlg;
}

class GameProperties;

class CustomGameDlg : public QWidget
{
    Q_OBJECT

public:
    explicit CustomGameDlg(QWidget *parent = 0);
    ~CustomGameDlg();
signals:
    void startNewGame(GameProperties& prop);
private:
    Ui::CustomGameDlg *ui;
private slots:
    void complicationTrigerred();
    void heightChanged();
    void onStart();
};

#endif // CUSTOMGAMEDLG_H
