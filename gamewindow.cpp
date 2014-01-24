#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QKeyEvent>
#include <QCloseEvent>

#include "about.h"
#include "gamewindow.h"
#include "gameengine.h"
#include "gamewidget.h"
#include "customgamedlg.h"
#include "keypad.h"
#include "field.h"
#include "keys.h"
#include "gameproperties.h"
#include "recordtable.h"
#include "newrecorddlg.h"
#include "recordsdlg.h"
#include "centerof.h"

GameWindow::GameWindow(GameWidget *wgt):QWidget(0)
{
    askedToClose=false;

    records=RecordTable::load(RecordTable::getTablePath());

    keypad=0;
    widget=wgt;
    widget->setParent(this);
    mainmenu=new QMenuBar(this);
    mainmenu->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Minimum);
    widget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    buildMenu();

    QVBoxLayout *vlay=new QVBoxLayout(this);
    vlay->addWidget(mainmenu);
    vlay->addWidget(widget);
    vlay->setMargin(0);
    vlay->setSpacing(0);
    setLayout(vlay);
    connect(wgt->getEngine(),SIGNAL(pauseTriggered(bool)),this,SLOT(pauseTriggered(bool)));

    setWindowTitle(tr("Tetris"));
    setWindowIcon(QIcon(QString(":/icon.png")));
}

GameWindow::~GameWindow(){
    delete records;
}

void GameWindow::buildMenu(){
    QMenu *filemenu=mainmenu->addMenu(tr("File"));
    QMenu *newgamemenu=filemenu->addMenu(tr("New game"));
    QAction *game5_10=newgamemenu->addAction(QString("5x10"));
    QAction *game10_20=newgamemenu->addAction(QString("10x20"));
    QAction *game15_30=newgamemenu->addAction(QString("15x30"));
    QAction *game20_40=newgamemenu->addAction(QString("20x40"));
    newgamemenu->addSeparator();
    QAction *customgame=newgamemenu->addAction(tr("Custom"));
    filemenu->addSeparator();
    QAction *exitAct=filemenu->addAction(tr("Exit"));
    QMenu *gameMenu=mainmenu->addMenu(tr("Game"));
    pauseAct=gameMenu->addAction(tr("Pause"));
    resetAct=gameMenu->addAction(tr("Reset"));
    gameMenu->addSeparator();
    QAction *recordAct=gameMenu->addAction(tr("Records"));
    pauseAct->setEnabled(false);
    resetAct->setEnabled(false);
    QMenu *helpMenu=mainmenu->addMenu(tr("Help"));
    QAction *aboutAct=helpMenu->addAction(tr("About"));

    exitAct->setShortcut(QKeySequence(QKeySequence::Quit));
    customgame->setShortcut(QKeySequence(QKeySequence::New));
    pauseAct->setShortcut(QKeySequence(QString(" ")));
    resetAct->setShortcut(QKeySequence(QKeySequence::Refresh));

    exitAct->setMenuRole(QAction::QuitRole);

    connect(game5_10,SIGNAL(triggered()),this,SLOT(startGame5_10()));
    connect(game10_20,SIGNAL(triggered()),this,SLOT(startGame10_20()));
    connect(game15_30,SIGNAL(triggered()),this,SLOT(startGame15_30()));
    connect(game20_40,SIGNAL(triggered()),this,SLOT(startGame20_40()));
    connect(customgame,SIGNAL(triggered()),this,SLOT(startCustomGame()));
    connect(exitAct,SIGNAL(triggered()),QApplication::instance(),SLOT(quit()));
    connect(pauseAct,SIGNAL(triggered()),this,SLOT(onPause()));
    connect(resetAct,SIGNAL(triggered()),widget->getEngine(),SLOT(reset()));
    connect(recordAct,SIGNAL(triggered()),this,SLOT(showRecords()));
    connect(aboutAct,SIGNAL(triggered()),this,SLOT(onAbout()));
}

void GameWindow::gameStarted(){
    resetAct->setEnabled(true);
    pauseAct->setEnabled(true);
}

void GameWindow::setKeypad(KeyPad *keypad){
    this->keypad=keypad;
}

void GameWindow::unsetKeypad(){
    keypad=0;
}

void GameWindow::gameOver(int score, GameProperties prop){
    if(score==0||!prop.isStandart()){
        askedToClose=false;
        return;
    }
    int overRecords=0;
    int width=prop.width();
    int height=prop.height();
    int count=records->count(width,height);
    for(int i=0;i<count;i++){
        Record *record=records->get(i,width,height);
        if(record->score()>=score)overRecords++;
    }
    if(overRecords>=10){
        askedToClose=false;
    }else{
        NewRecordDlg *dialog=new NewRecordDlg();
        dialog->setAttribute(Qt::WA_DeleteOnClose);
        centerOf(this,dialog);

        dialog->setConfigs(score,width,height);
        connect(dialog,SIGNAL(cancel()),this,SLOT(close()));
        connect(dialog,SIGNAL(accept(Record)),this,SLOT(acceptRecord(Record)));

        dialog->show();
    }
}

void GameWindow::acceptRecord(Record record){
    records->add(record);
    records->save(RecordTable::getTablePath());
    if(askedToClose)close();
}

void GameWindow::pauseTriggered(bool paused){
    pauseAct->setText(paused?tr("Resume"):tr("Pause"));
}

void GameWindow::startGame5_10(){
    GameEngine *engine=widget->getEngine();
    GameProperties prop=GameProperties(5,10);
    engine->startGame(prop);
    gameStarted();
}

void GameWindow::startGame10_20(){
    GameEngine *engine=widget->getEngine();
    GameProperties prop=GameProperties(10,20);
    engine->startGame(prop);
    gameStarted();
}

void GameWindow::startGame15_30(){
    GameEngine *engine=widget->getEngine();
    GameProperties prop=GameProperties(15,30);
    engine->startGame(prop);
    gameStarted();
}

void GameWindow::startGame20_40(){
    GameEngine *engine=widget->getEngine();
    GameProperties prop=GameProperties(20,40);
    engine->startGame(prop);
    gameStarted();
}

void GameWindow::startCustomGame(){
    CustomGameDlg *dialog=new CustomGameDlg();
    centerOf(this,dialog);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    connect(dialog,SIGNAL(startNewGame(GameProperties&)),this,SLOT(startGame(GameProperties&)));
    dialog->show();
}

void GameWindow::startGame(GameProperties& prop){
    widget->getEngine()->startGame(prop);
    gameStarted();
}

void GameWindow::closeEvent(QCloseEvent *ev){
    if(ev->spontaneous()&&widget->getEngine()->needToSaveRecord()){
        askedToClose=true;
        emit dropGame();
        if(askedToClose)ev->ignore();
        else ev->accept();
    }
    else ev->accept();
}

void GameWindow::keyPressEvent(QKeyEvent *ev){
    if(ev->key()==Qt::Key_Space)return;
    if(keypad!=0)keypad->keyPress(ev);
}

void GameWindow::keyReleaseEvent(QKeyEvent *ev){
    if(keypad!=0)keypad->keyRelease(ev);
}

void GameWindow::onPause(){
    keypad->keyPress(KeyPause);
    keypad->keyRelease(KeyPause);
}

void GameWindow::onAbout(){
    About *aboutDlg=new About();
    centerOf(this,aboutDlg);
    aboutDlg->setAttribute(Qt::WA_DeleteOnClose);
    aboutDlg->show();
}

void GameWindow::showRecords(){
    RecordsDlg *dialog=new RecordsDlg();
    centerOf(this,dialog);
    dialog->setRecordTable(records);
    dialog->setAttribute(Qt::WA_DeleteOnClose);
    dialog->show();
}
