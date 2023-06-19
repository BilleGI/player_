#include <QtGui/QtGui>
#include <QApplication>

#include <QPushButton>
#include <QMediaPlayer>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QSlider>
#include <QFileDialog>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    QWidget playerWindow;
    QVBoxLayout vbox(&playerWindow);
    QHBoxLayout buttons;
    QSlider *songSlider = new QSlider(&playerWindow);
    songSlider->setOrientation(Qt::Horizontal);
    vbox.addWidget(songSlider);

    auto *openFileButton = new QPushButton("Open", &playerWindow);
    auto *playMediaButton = new QPushButton("Play", &playerWindow);
    auto *pauseMediaButton = new QPushButton("Pause", &playerWindow);

    buttons.addWidget(openFileButton);
    buttons.addWidget(playMediaButton);
    buttons.addWidget(pauseMediaButton);

    vbox.addLayout(&buttons);

    QString filePath;

    auto *player = new QMediaPlayer(&playerWindow);

    bool isPlaying = false;

    QObject::connect(openFileButton, &QPushButton::clicked, [&filePath, player, &isPlaying]()
                     {
        filePath = QFileDialog::getOpenFileName(nullptr, "Open mp3 song", "/home/", "mp3 files (*.mp3)");
        player->stop();
        isPlaying = false;
    });

    QObject::connect(playMediaButton, &QPushButton::clicked, [&isPlaying, songSlider, player, &filePath]()
                     {
        if(!isPlaying)
        {
            player->setSource(QUrl::fromLocalFile(filePath));
//            player->setVolume(75);
            QObject::connect(player, &QMediaPlayer::durationChanged, [songSlider](qint64 duration)
                             {
                songSlider->setMinimum(0);
                songSlider->setMaximum(duration);
            });

            QObject::connect(player, &QMediaPlayer::positionChanged, [songSlider](qint64 position)
                             {
                songSlider->setValue(position);
            });
            isPlaying = true;
        }
            player->play();
    });

    playerWindow.show();

    return app.exec();
}
