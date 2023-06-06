//
// Created by 32725 on 2023/6/3.
//

#ifndef SUMARY_SERVER_H
#define SUMARY_SERVER_H

#include <QThread>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QCryptographicHash>
#include <QFIle>
#include "tools.h"

struct ServerSend;
class zServer : public QWidget {
	Q_OBJECT
public:
	explicit zServer(QWidget*parent= nullptr);
	~zServer()override;
private:
	tools::IPPort* ip;
	QTcpServer* server;
	ServerSend* send= nullptr;
	QPushButton* sendButton;
	QThread* sendThread= nullptr;
	QString fileName;
};

struct ServerSend: public QObject{
Q_OBJECT
public:
	explicit ServerSend(QTcpSocket*s, QObject*parent= nullptr): socket(s), QObject(parent){}
	void Send(const QString&fileName){
			qDebug()<<fileName;
			QFile file(fileName);
			if(!file.open(QIODevice::ReadOnly)){
				qDebug()<<"error";
				return;
			}
			QString Md5=QCryptographicHash::hash(file.readAll(),QCryptographicHash::Md5).toHex();
			file.seek(0);
			socket->write(("file##"+QByteArray::number(file.size())
			+"##."+(fileName.section('.',-1,-1)==fileName?".*":fileName.section('.',-1,-1))
			+"##"+Md5.toUtf8()).toUtf8());
			socket->flush();
			qDebug()<<"Md5:"<<Md5;
			QThread::msleep(2000);
			qint64 size=file.size();
			qint64 sendSize=0;
			char buffer[1024*4]{0};
			while(sendSize<size){
				auto tSize=file.read(buffer,sizeof(buffer));
				socket->write(buffer,tSize);
				sendSize+=tSize;
			}
			file.close();
	}
	~ServerSend() override{
		delete socket;
	}
private:
	QTcpSocket* socket;
};

#endif //SUMARY_SERVER_H
