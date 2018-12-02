#include "loopplayer.h"

#include <iostream>
#include <chrono>

LoopPlayer::LoopPlayer(QObject *parent) : QThread(parent)
{
    stop = true;
}

LoopPlayer::~LoopPlayer()
{
    mutex.lock();
    stop = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool LoopPlayer::loadVideo(std::string filename)
{
    cv::VideoCapture capture;
    capture.open(filename);
    if (capture.isOpened())
    {
        fps = static_cast<int>(capture.get(CV_CAP_PROP_FPS));

        frameCount = static_cast<int>(capture.get(CV_CAP_PROP_FRAME_COUNT));
        duration = static_cast<long>(double(frameCount) / double(fps) * 1000);

        cv::Mat frame;
        while (capture.read(frame))
        {
            if (frame.channels() == 3)
            {
                cv::cvtColor(frame, frame, CV_BGR2RGB);
            }
            frames.push_back(frame.clone());
        }

        capture.release();
        return true;
    }

    return false;
}

void LoopPlayer::setPlaybackRate(double rate) {
    playbackRate = rate;
}

long LoopPlayer::getDuration() const
{
    return duration;
}

bool LoopPlayer::isStopped() const
{
    return stop;
}

void LoopPlayer::play()
{
    stop = stop ? false : true;
    if (!isRunning()) {
        start(LowPriority);
    }
}

void LoopPlayer::pause()
{
    stop = true;
}

void LoopPlayer::run()
{
    while (true)
    {
        if (!stop)
        {
            if (currentFrameIndex >= frameCount) {
                currentFrameIndex = 0;
            }
            auto it = frames.begin() + currentFrameIndex;
            cv::Mat frame = *it;
            if (frame.channels() == 3)
            {
                img = QImage(const_cast<const unsigned char*>(frame.data),
                             frame.cols,
                             frame.rows,
                             QImage::Format_RGB888);
            }
            else
            {
                img = QImage(const_cast<const unsigned char*>(frame.data),
                             frame.cols,
                             frame.rows,
                             QImage::Format_Indexed8);
            }
            emit processedImage(img);
            currentFrameIndex++;
        }
        int delay = int(1000.0 / fps * playbackRate);
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}


