#include "Game.h"
#include "MainWindow.h"
#include <QtGlobal>
#include <QGridLayout>
#include <QPoint>
#include <QPushButton>
#include <QTime>
#include "QMessageBox"
#include <cstdlib>
#include <QTime>
#include <QElapsedTimer>
#include "QInputDialog"
#include <QFile>
#include <QTextStream>
#include <QSound>

   QElapsedTimer t;
Game::Game(QWidget*)
{
    t.start();
    grid = new QGridLayout(this);
    grid->setHorizontalSpacing(1);
    grid->setVerticalSpacing(1);
    grid->setContentsMargins(2, 2, 2, 2);

    QTime midnight(0, 0, 0);
    srand(midnight.secsTo(QTime::currentTime()));

    // картинки
    for(int i=0;i<15;i++)
    {
             if(i==0)px[i]=new QPixmap(":/resources/1.jpg");    else if(i==7)px[i]=new QPixmap(":/resources/8.jpg");
        else if(i==1)px[i]=new QPixmap(":/resources/2.jpg");    else if(i==8)px[i]=new QPixmap(":/resources/9.jpg");
        else if(i==2)px[i]=new QPixmap(":/resources/3.jpg");    else if(i==9)px[i]=new QPixmap(":/resources/10.jpg");
        else if(i==3)px[i]=new QPixmap(":/resources/4.jpg");    else if(i==10)px[i]=new QPixmap(":/resources/11.jpg");
        else if(i==4)px[i]=new QPixmap(":/resources/5.jpg");    else if(i==11)px[i]=new QPixmap(":/resources/12.jpg");
        else if(i==5)px[i]=new QPixmap(":/resources/6.jpg");    else if(i==12)px[i]=new QPixmap(":/resources/13.jpg");
        else if(i==6)px[i]=new QPixmap(":/resources/7.jpg");    else if(i==13)px[i]=new QPixmap(":/resources/14.jpg");
                                                            else if(i==14)px[i]=new QPixmap(":/resources/15.jpg");
    }
    int n;

    do
    {
        numbers.clear();

        for(int i = 0; i < 15; i++)
        { // случайные числа
            do n = rand() % 15 + 1;
            while(numbers.contains(n));
            numbers << n;
        }

        n = 0;

        for(int i = 2; i <= 15; i++)
        for(int j = 0; j < numbers.indexOf(i); j++)
        {
            if(numbers[j] < i)
            {
                ++n;
            }
        }
    }
    while(n%2 == 1);

        do path.setY(rand() % 4);
        while(n%2 != path.y()%2);

        path.setX(rand() % 4);

        n = 0;

        for(int y = 0; y < 4; ++y) // строка
        for(int x = 0; x < 4; ++x) // столбец
        {
            if(path.x() == x && path.y() == y)
                continue;

            createButton(NULL, numbers[n++], x, y);
        }
        setLayout(grid);
}
void Game::move()
{
    int x, y, rs, cs;
    QPushButton* clickedBtn = static_cast<QPushButton*>(sender());
    QSound::play("://resources/click.wav");
    grid->getItemPosition(grid->indexOf(clickedBtn), &y, &x, &rs, &cs);

    if((path.x() == x && (path.y() == y+1 || path.y() == y-1))
    || (path.y() == y && (path.x() == x+1 || path.x() == x-1))) // Можно ли двигать кнопку?
    {
        // удаляем кнопку со старого места
        grid->removeWidget(clickedBtn);
        // и добавляем на свободную ячейку
        createButton(clickedBtn, 0, path.x(), path.y());
        // и обновляем координаиы свободной ячейки
        path = QPoint(x, y);
        checkGameOver(); // проверка на конец игры
    }
}

void Game::checkGameOver()
{
    Q_ASSERT(grid->count() == numbers.size());

    int i=1, n=0, tim;

    for(int y = 0; y < grid->rowCount(); ++y) // строка
    for(int x = 0; x < grid->columnCount(); ++x) // столбец
    {
        if(grid->itemAtPosition(y, x) == 0)
            continue;
        n = numbers.indexOf(i++);
        if(buttons[n] != (QPushButton*)grid->itemAtPosition(y, x)->widget())
            return;
    }

    // проверка, свободна ли последняя ячейка
    if(path.y() == grid->rowCount()-1 && path.x() == grid->columnCount()-1)
    { // игра окончена
        // блокировка всех кнопок
        for(QList<QPushButton*>::const_iterator it = buttons.begin(); it != buttons.end(); ++it)
            (*it)->setDisabled(true);
        tim=t.elapsed()/1000;
        bool bOk;
        QString str = QInputDialog::getText( 0,
        "Input",
        QString(" Поздравляем!\n\n Ваш результат: %1 (сек)\n\n Введите своё имя:").arg(tim),
        QLineEdit::Normal,
        "",
        &bOk
        );
        if (!bOk) {
        // Была нажата кнопка Cancel
        }
        QFile file("file.txt");
        if (file.open(QIODevice::WriteOnly |QIODevice::Text | QIODevice::Append ))
        {
        QTextStream out(&file);
        out<<"\n"<<str<<"\t\t"<<tim;
        } file.close();
    }
}

void Game::createButton(QPushButton* b, int no, int x, int y) // Создание кнопки
{
    QPushButton* btn = b;
    if(!btn)
    {
        btn = new QPushButton();//(QString("%1").arg(no));
        buttons << btn;
        connect(btn, SIGNAL(clicked()), this, SLOT(move()));
        btn->setFixedSize(150,150);

        QIcon ButtonIcon(*px[no-1]);
        btn->setIcon(ButtonIcon);
        btn->setIconSize(QSize(150,150));

    }
    grid->addWidget(btn, y, x);
}
