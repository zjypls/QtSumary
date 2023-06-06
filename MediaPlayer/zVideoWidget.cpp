//
// Created by 32725 on 2023/6/6.
//
#include <QVideoSink>
#include <QFileDialog>
#include "zVideoWidget.h"

using namespace std::literals;

Player::Player(QWidget *parent): QWidget(parent) {
	this->resize(1070,650);
	playIcon=new QIcon{sourceDir+"Assets/Icon/play.png"};
	pauseIcon=new QIcon{sourceDir+"Assets/Icon/pause.png"};
	play=new QPushButton{*playIcon,"",this};
	openFile=new QPushButton{"Open",this};
	play->resize(100,25);
	play->move(0,625);
	openFile->resize(100,25);
	openFile->move(100,625);
	play->show();
	videoWidget=new QVideoWidget{this};
	videoWidget->resize(1070,600);
	videoWidget->move(0,0);
	player=new QMediaPlayer{this};
	audioOutput=new QAudioOutput{QMediaDevices::defaultAudioOutput(),this};
	audioOutput->setVolume(70);
	player->setVideoOutput(videoWidget);
	player->setAudioOutput(audioOutput);
	player->setLoops(QMediaPlayer::Loops::Infinite);
	player->setSource(url);
	slider=new QSlider{Qt::Horizontal,this};
	slider->resize(1000,25);
	slider->move(0,600);
	slider->show();
	message=new QLabel{this};
	message->resize(70,25);
	message->move(1000,600);
	message->show();
	connect(player,&QMediaPlayer::errorOccurred,this,[=](auto error,auto des){
		if(error!=QMediaPlayer::Error::NoError)
			qDebug()<<"Error:"<<des;
	});
	connect(openFile,&QPushButton::clicked,[&]{
		if(player->playbackState()==QMediaPlayer::PlaybackState::PlayingState)
			player->stop();
		QString path=QFileDialog::getOpenFileName(this,"Open File",sourceDir+"Assets","Video (*.mp4)");
		if(!path.isEmpty()) {
			url=QUrl::fromLocalFile(path);
			player->setSource(url);
		}
	});
	connect(player,&QMediaPlayer::durationChanged,[&](auto d){
		slider->setMaximum(d);
		duration=d;
		message->setText(QString{"0/%1 s"}.arg(d/1000));
	});
	connect(play,&QPushButton::clicked,[&]{
		if(player->playbackState()==QMediaPlayer::PlaybackState::PlayingState) {
			pausePos=player->position();
			player->pause();
			play->setIcon(*playIcon);
		}
		else {
			player->setPosition(pausePos);
			player->play();
			play->setIcon(*pauseIcon);
		}
	});
	connect(player,&QMediaPlayer::playbackStateChanged,[&](auto d){
		if(d==QMediaPlayer::PlaybackState::StoppedState)
			play->setIcon(*playIcon);
		else
			play->setIcon(*pauseIcon);
	});
	connect(player,&QMediaPlayer::positionChanged,[&](auto d){
		slider->setValue(d);
		message->setText(QString{"%1/%2 s"}.arg(d/1000).arg(duration/1000));
	});
	connect(slider,&QSlider::sliderMoved,[&](auto d){
		player->setPosition(d);
		pausePos=d;
		message->setText(QString{"%1/%2 s"}.arg(d/1000).arg(duration/1000));
	});
	connect(slider,&QSlider::sliderPressed,[&]{
		player->pause();
	});
	connect(slider,&QSlider::sliderReleased,[&]{
		player->setPosition(slider->value());
		player->play();
	});
}

Player::~Player() {

}
