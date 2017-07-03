#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include "Game.h"
class QHBoxLayout;
class QLabel;
class QSpinBox;
class QVBoxLayout;
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = 0);
    ~Form();
public slots:
    void newGame();
    void exitGame();
private slots:
private:
    Ui::Form *ui;
    QHBoxLayout* settingslayout;
    QVBoxLayout* layout;
    QTimer* timer;
    Game* game;
};

#endif // FORM_H
