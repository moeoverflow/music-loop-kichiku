#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <aubio/aubio.h>

#include "aubiobeat.h"
#include "utils.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    const auto audioSource = "/Users/shincurry/dev/music-loop-kichiku/test_data/audio3.mp3";
    audioPlayer = new QMediaPlayer;
    audioPlayer->setNotifyInterval(1);
    audioPlayer->setMedia(QUrl::fromLocalFile(audioSource));
    QObject::connect(audioPlayer, SIGNAL(positionChanged(qint64)), this, SLOT(audioPositionChanged(qint64)));

    beats = find_beat(audioSource);


    const auto videoSource = "/Users/shincurry/dev/music-loop-kichiku/test_data/video4.mp4";
    videoPlayer = new LoopPlayer();
    videoPlayer->loadVideo(videoSource);
    QObject::connect(videoPlayer, SIGNAL(processedImage(QImage)), this, SLOT(updateLoopPlayerUI(QImage)));


    audioPlayer->play();
    videoPlayer->play();
}

void MainWindow::audioPositionChanged(qint64 position) {
    auto it = std::find(beats.begin(), beats.end(), long(position));
    if (it != beats.end()) {
        qint64 videoDuration = videoPlayer->getDuration();
        qint64 beatDuration = beatDuration = qint64(*(it+1) - *it);
        auto rate = double(beatDuration) / double(videoDuration);

        videoPlayer->pause();
        videoPlayer->setPlaybackRate(rate);
        videoPlayer->play();
    }
}

void MainWindow::updateLoopPlayerUI(QImage img)
{
    if (!img.isNull())
    {
        ui->videoScreen->setAlignment(Qt::AlignCenter);
        ui->videoScreen->setPixmap(QPixmap::fromImage(img)
                             .scaled(
                                 ui->videoScreen->size(),
                                 Qt::KeepAspectRatio,
                                 Qt::FastTransformation)
                             );
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
