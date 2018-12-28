#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QtMath>
#include <memory>
#include <QMediaPlayer>
#include "config.h"
#include "controller.h"
#include "textview.h"
#include "scene.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void keyPressEvent(QKeyEvent * event);
    void userSetting();

signals:
    void ProtagonistMove_signal(DIRECTION d);
    void autoPlay_signal();

public slots:
    void setMessage(QString str);
    void setTextView(QString str);
    void on_slider_resize_valueChanged(int value);
    void on_slider_animation_valueChanged(int value);
    void on_new_game_triggered();
    void on_restart_game_triggered();
    void on_auto_track_changed();
    void on_pause_game_changed();
    void centerPro();
    void loose_slot();
    void win_slot();
    void start();

private slots:
    void on_auto_play_button_clicked();
    void on_find_path_clicked();
    void on_path_v_clicked();

private:
    Ui::MainWindow *ui;
    QString filename;
    bool isPathfinding=false;
    std::unique_ptr<Controller> myController;
    std::shared_ptr<Scene> myScene;
    std::shared_ptr<TextView> myTextView;
    QGraphicsView * game_view;
    QMediaPlayer *player;
    unsigned int nrOfPacks = 5;//default value
    unsigned int nrOfEnemies = 5;//default value
};

#endif // MAINWINDOW_H
