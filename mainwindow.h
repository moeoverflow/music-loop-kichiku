#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>

#include "loopplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void audioPositionChanged(qint64 position);
    void updateLoopPlayerUI(QImage img);

private:
    Ui::MainWindow *ui;
    QMediaPlayer *audioPlayer;

    LoopPlayer *videoPlayer;

    std::vector<long> beats;
};

#endif // MAINWINDOW_H
