#include "form.h"
#include "ui_form.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QTimer>
#include <QSpinBox>
//#include <QLCDNumber>

Form::Form(QWidget *parent) : game(NULL),
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    layout  = new QVBoxLayout(this);
    settingslayout = new QHBoxLayout;

    QPushButton* newgame = new QPushButton();
    QPushButton* exitgame = new QPushButton();
    QPixmap newG(":/resources/new.png");
    QPixmap exG(":/resources/exit.png");
    QIcon newGIcon(newG);
    QIcon exGIcon(exG);
    newgame->setIcon(newGIcon);
    exitgame->setIcon(exGIcon);
    newgame->setIconSize(QSize(304,70));
    exitgame->setIconSize(QSize(290,70));
    connect(newgame,SIGNAL(clicked()),this, SLOT (newGame()));
    connect(exitgame,SIGNAL(clicked()),this, SLOT (exitGame()));
    settingslayout->addWidget(newgame);
    settingslayout->addWidget(exitgame);
    layout->setContentsMargins(2,2,2,2);
    layout->addLayout(settingslayout);
    newGame();
    setLayout(layout);
}

Form::~Form()
{
    delete ui;
}
void Form::newGame()
{
    if(game)
    {
        layout->removeWidget(game);
        delete game;
    }
    game = new Game(this);
    layout->addWidget(game);
    layout->update();
    game->hide();
    game->show();
    resize(sizeHint());
}
void Form::exitGame()
{
    MainWindow *f = new MainWindow();
    f->show();
    this->close();
}
