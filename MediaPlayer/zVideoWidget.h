#ifndef ZVIDEOWIDGET_H
#define ZVIDEOWIDGET_H
#include <QWidget>
#include <QLabel>
#include <QMovie>
#include <QFile>
#include <QMediaPlayer>
#include <QMediaMetaData>
#include <QVideoWidget>
#include <QAudioOutput>
#include <QAudioDevice>
#include <QMediaDevices>
#include <QPushButton>
#include <QSlider>
const QString sourceDir{Z_SOURCE_DIR};
class Player:public QWidget{
public:
	explicit Player(QWidget *parent = nullptr);
	~Player() override;

private:
	QPushButton *play,*openFile;
	QVideoWidget* videoWidget;
	QMediaPlayer *player;
	QAudioOutput *audioOutput;
	QSlider* slider;
	QLabel* message;
	QUrl url{sourceDir+"Assets/Video/videoplayback.mp4"};
	qint64 duration,pausePos=0;
	QIcon *playIcon,*pauseIcon;
};


#endif // ZVIDEOWIDGET_H