#include "gameoverdialog.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

GameOverDialog::GameOverDialog()
{
    QHBoxLayout * layout = new QHBoxLayout(this);

    QPushButton *restart = new QPushButton("&Restart",this);
    QPushButton *cancel = new QPushButton("&Cancel",this);

    connect(restart, SIGNAL(clicked()),this,SLOT(accept()));
    connect(cancel, SIGNAL(clicked()),this,SLOT(reject()));



    layout->addWidget(restart);
    layout->addWidget(cancel);
}
