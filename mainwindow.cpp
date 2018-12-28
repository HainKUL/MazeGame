#include "gameoverdialog.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QFileDialog>
#include <QMessageBox>
#include <iostream>
#include <QFormLayout>
#include <QLineEdit>
#include <QIntValidator>
#include <QDialogButtonBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    game_view = new QGraphicsView();
    userSetting();

    myController = std::make_unique<Controller>(filename, nrOfEnemies, nrOfPacks);
    myScene = std::make_shared<Scene>(myController->myModel);//scene and controller shared one model
    myTextView = std::make_shared<TextView>(myController->myModel);//textview and controller shared one model
    player = new QMediaPlayer(this);
    player->setMedia(QUrl("qrc:/sounds/bgm.mp3"));
    player->setVolume(30);

    this->setCentralWidget(game_view);
    ui->setupUi(this);
    ui->game_view->setScene(myScene.get());
    ui->game_view->centerOn(myScene->proView);
    ui->slider_resize->setValue(50);
    ui->hp_bar->setValue(100);
    ui->energy_bar->setValue(100);

    //Link signals and slots
    connect(myController->myModel->myProtagonist.get(),SIGNAL( healthChanged(int)),ui->hp_bar,SLOT(setValue(int)));
    connect(myController->myModel->myProtagonist.get(),SIGNAL( energyChanged(int)),ui->energy_bar,SLOT(setValue(int)));
    connect(this, SIGNAL(autoPlay_signal()), myController.get(), SLOT(autoPlay_slot()));
    connect(myTextView.get(),SIGNAL(redraw_textbrowser(QString)),this,SLOT(setTextView(QString)));
    connect(this, SIGNAL(ProtagonistMove_signal(DIRECTION)), myController.get(), SLOT(ProtagonistMove_slot(DIRECTION)));
    connect(myScene.get(),SIGNAL(centerMe()),this,SLOT(centerPro()));
    connect(myController.get(),SIGNAL(sendMessage(QString)),this,SLOT(setMessage(QString)));
    connect(myController->myModel.get(),SIGNAL(goToPos(int,int)),myController.get(),SLOT(goClickedPos(int, int )));
    connect(myController.get(),SIGNAL(loose()),this,SLOT(loose_slot()));
    connect(myController.get(),SIGNAL(win()),this,SLOT(win_slot()));

    player->play();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::userSetting()
{
    //select world map
    filename = QFileDialog::getOpenFileName(
                this,
                tr("Choose World"),
                "/home",
                "Image File (*.png)"
                );

    if(filename.isEmpty())
    {

        //using default world map
        filename = ":/images/maze_5.png";
        QMessageBox::information(this, tr("User setting"),tr("Using default setting for world map"));
    }
    else
    {
        QMessageBox::information(this, tr("File Name"), filename);
    }

    //set ememy and hp number
    QDialog dialog(this);
    QFormLayout formLayout(&dialog);

    QLineEdit * enemyLineEdit = new QLineEdit(&dialog);
    QLineEdit * packLineEdit = new QLineEdit(&dialog);

    //set limit to integer number
    enemyLineEdit->setValidator(new QIntValidator(0,100,this));
    packLineEdit->setValidator(new QIntValidator(0,100,this));

    formLayout.addRow(new QLabel("Choose the number of enemies and health packs"));
    formLayout.addRow(tr("&Enemies:"),enemyLineEdit);
    formLayout.addRow(tr("&HealthPacks:"),packLineEdit);

    //add check button--ok and cancel
    QDialogButtonBox buttonBox (QDialogButtonBox::Ok
                                | QDialogButtonBox::Cancel);
    connect(&buttonBox, SIGNAL(accepted()),&dialog,SLOT(accept()));
    connect(&buttonBox, SIGNAL(rejected()),&dialog,SLOT(reject()));

    formLayout.addRow(&buttonBox);

    //show dialog
    int result = dialog.exec();//exec return value is int

    //check if the button is checked
    if(result == QDialog::Accepted)
    {
        if(!enemyLineEdit->text().isEmpty()&&!packLineEdit->text().isEmpty())
        {//if parameters are filled in
            //get the unsigned int value from qLineEdit
            nrOfEnemies = enemyLineEdit->text().toUInt();
            nrOfPacks = packLineEdit->text().toUInt();
            std::cout<<"loading map ..."<<std::endl;
        }
        else
        {
            QMessageBox::warning(this,
                                     tr("Warning"),
                                     tr("Please fill in the parameters!"));
        }
    }
    else
    {//button canceled
        QMessageBox::information(this, tr("User setting"),tr("Using default setting for parameters"));
        std::cout<<"loading map ..."<<std::endl;
        return;
    }
}

void MainWindow::keyPressEvent(QKeyEvent * event){

    // Set KeyPressevent to make protagonist move.
    if(event->key()==Qt::Key_A){
        emit ProtagonistMove_signal(LEFT);
    }
    else if(event->key()==Qt::Key_W){
        emit ProtagonistMove_signal(UP);
    }
    else if(event->key()==Qt::Key_S){
        emit ProtagonistMove_signal(DOWN);
    }
    else if(event->key()==Qt::Key_D){
        emit ProtagonistMove_signal(RIGHT);
    }
}


void MainWindow::setMessage(QString str)
{
    ui->information->insertPlainText(str);
}

void MainWindow::setTextView(QString str)
{
    ui->textView->setText(str);
}

void MainWindow::on_find_path_clicked()//find path, switch scenes
{
    if(isPathfinding==false)
    {
        ui->game_view->setScene(myController->myModel->getMyTester().get());
        isPathfinding=true;
    }

    else
    {
        isPathfinding=false;
        ui->game_view->setScene(myScene.get());
    }
}

void MainWindow::on_auto_play_button_clicked()//auto play
{
    if(ui->auto_play_button->isChecked()){
        myController->setAutoPlay(true);
        ui->path_v->setDisabled(true);
    } else {
        myController->setAutoPlay(false);
        ui->path_v->setDisabled(false);
    }
    for(auto paV:myScene->pathView){
        myScene->removeItem(paV);
    }
    std::vector<QGraphicsPixmapItem*>().swap(myScene->pathView);
    emit autoPlay_signal();
}

void MainWindow::on_slider_resize_valueChanged(int value)
{
    qreal scale = qPow(qreal(2),(value-50)/qreal(50));
    QMatrix oldMatrix = ui->game_view->matrix();
    ui->game_view->resetMatrix();
    ui->game_view->translate(oldMatrix.dx(),oldMatrix.dy());
    ui->game_view->scale(scale,scale);
}

void MainWindow::on_slider_animation_valueChanged(int value)
{
    float final = (60-value)/10;
    myScene->proView->setScale(final);
    for(auto xene:myScene->xenemies){
        xene->setScale(final);
    }
    myController->setScale(final);
}

void MainWindow::on_restart_game_triggered()
{
    start();
    player->play();
}

void MainWindow::on_new_game_triggered()
{
    userSetting();
    start();
    player->play();
}

void MainWindow::on_auto_track_changed()
{
    if (ui->auto_track->isChecked()){
        myScene->setTracked(true);
    } else {
        myScene->setTracked(false);
    }
}

void MainWindow::on_pause_game_changed()
{
    if(ui->pause_game->isChecked()){
        myController->setAutoPlay(false);
        myController->setPause(true);
        myScene->setPause(true);
        ui->auto_play_button->setDisabled(true);
    }else {
        ui->auto_play_button->setDisabled(false);
        if(ui->auto_play_button->isChecked()){
            myController->setAutoPlay(true);
        } else myController->setAutoPlay(false);
        myController->setPause(false);
        myScene->setPause(false);
        myController->xEnemyMovingEnemy();
        for(auto paV:myScene->pathView){
            myScene->removeItem(paV);
        }
        std::vector<QGraphicsPixmapItem*>().swap(myScene->pathView);
        emit autoPlay_signal();
    }
}

void MainWindow::centerPro()
{
    ui->game_view->centerOn(myScene->proView);
}

void MainWindow::loose_slot()
{
    GameOverDialog *gameover = new GameOverDialog();
    int result = gameover->exec();////exec return value is int
    //check if the button is checked
    if(result == GameOverDialog::Accepted)
    {//restart game
        on_new_game_triggered();
    }
    else
    {//button canceled

        //QMessageBox::information(gameover, tr("Game Over"),tr("you pressed cancel!"));
        return;
    }
}

void MainWindow::win_slot()
{
    QMessageBox::information(this, tr("Congradulations"),tr("You Win!"));
}

void MainWindow::start()
{
    myController = std::make_unique<Controller>(filename, nrOfEnemies, nrOfPacks);
    myScene = std::make_shared<Scene>(myController->myModel);//scene and controller shared one model
    myTextView = std::make_shared<TextView>(myController->myModel);//textview and controller shared one model

    ui->game_view->setScene(myScene.get());
    ui->game_view->centerOn(myScene->proView);
    ui->slider_resize->setValue(50);
    ui->hp_bar->setValue(100);
    ui->energy_bar->setValue(100);

    connect(this, SIGNAL(ProtagonistMove_signal(DIRECTION)), myController.get(), SLOT(ProtagonistMove_slot(DIRECTION)));
    connect(myScene.get(),SIGNAL(centerMe()),this,SLOT(centerPro()));
    connect(myController.get(),SIGNAL(sendMessage(QString)),this,SLOT(setMessage(QString)));
    connect(myController->myModel.get(),SIGNAL(goToPos(int,int)),myController.get(),SLOT(goClickedPos(int, int )));
    connect(myController.get(),SIGNAL(loose()),this,SLOT(loose_slot()));

    ui->game_view->setScene(myScene.get());
    ui->game_view->centerOn(myScene->proView);
    ui->slider_resize->setValue(50);
    ui->hp_bar->setValue(100);
    ui->energy_bar->setValue(100);

    connect(myController->myModel->myProtagonist.get(),SIGNAL( healthChanged(int)),ui->hp_bar,SLOT(setValue(int)));
    connect(myController->myModel->myProtagonist.get(),SIGNAL( energyChanged(int)),ui->energy_bar,SLOT(setValue(int)));
    //connect(this, SIGNAL(findPath_signal()), myController.get(), SLOT(findPath_slot()));
    connect(this, SIGNAL(autoPlay_signal()), myController.get(), SLOT(autoPlay_slot()));

}

//change parameter of a*
void MainWindow::on_path_v_clicked()
{
    myController->myModel->getPathfinder()->setWeight(ui->weight->value());
    myController->myModel->getPathfinder()->setGcost(ui->cost->value());

    //change the parameters for Tester
    myController->myModel->getMyTester()->getPathfinder()->setWeight(ui->weight->value());
    myController->myModel->getMyTester()->getPathfinder()->setGcost(ui->cost->value());
    QString str = "You set weight as ";
    str.append(QString::number(ui->weight->value())).append(", cost as ").append(QString::number(ui->cost->value())).append("\n");
    ui->information->insertPlainText(str);
    qDebug()<<ui->weight->value();
    qDebug()<<ui->cost->value();
}
