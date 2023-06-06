//
// Created by 32725 on 2023/6/3.
//

#ifndef SUMARY_CLIENT_H
#define SUMARY_CLIENT_H

#include <QWidget>
#include <QTcpSocket>
#include <QTextEdit>
#include <QThread>
#include <QMessageBox>
#include <QFileDialog>
#include <QCryptographicHash>
#include "tools.h"

class ClientSend : public QObject {
Q_OBJECT
public:
	explicit ClientSend(QObject *parent = nullptr) : QObject(parent) {
		socket = nullptr;
	}

	~ClientSend() override {
		if (socket != nullptr)
			socket->close();
		delete socket;
	}

	bool Connected() {
		return socket != nullptr && socket->state() == QAbstractSocket::ConnectedState;
	}

public slots:

	void Connect(const QHostAddress &address, quint16 port) {
		if (socket == nullptr) { socket = new QTcpSocket{}; }
		connect(socket, &QTcpSocket::readyRead, this, &ClientSend::Receive);
		socket->connectToHost(address, port);
		if (!socket->waitForConnected(3000)) {
			qDebug() << "error";
			return;
		}
	}

	void DisConnect() {
		if (socket != nullptr)
			socket->disconnectFromHost();
	}

	void Receive() {
		QString headMessage = socket->readAll();
		if (headMessage.isEmpty())
			return;
		auto sections = headMessage.split("##");
		qDebug() << "Tag:" + sections[0] << Qt::endl
		         << "Size:" << sections[1] << Qt::endl
		         << "Type:" << sections[2] << Qt::endl
		         << "Md5:" << sections[3];
		bool ok = false;
		uint64_t tempSize = sections[1].toULongLong(&ok);
		if (!ok) {
			qDebug() << "error";
			return;
		}
		fileName = QFileDialog::getSaveFileName(nullptr, "save file", QDir::currentPath(),sections[2]);
		if (fileName.isEmpty()) {
			fileName = "temp";
		}
		totalSize = tempSize;
		receiveSize = 0;
		qDebug() << "rec:";
		QFile file(fileName + sections[2]);
		if (!file.open(QIODevice::ReadWrite)) {
			qDebug() << "error";
			return;
		}
		char buffer[1024 * 4]{0};
		int64_t recsize;
		auto start = std::chrono::system_clock::now();
		while (receiveSize < totalSize) {
			recsize = socket->read(buffer, sizeof(buffer));
			file.write(buffer, recsize);
			receiveSize += recsize;
		}
		auto end = std::chrono::system_clock::now();
		qDebug() << "end";
		qDebug() << "time spend(ms):" << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		QString recMd5 = QCryptographicHash::hash(file.readAll(), QCryptographicHash::Md5).toHex();
		qDebug() << "Rec Md5:" << recMd5;
		qDebug() << "IsSame:" << (recMd5 == sections[3]);
		file.close();
		receiveSize = 0;
	}

private:
	QTcpSocket *socket = nullptr;
	QString fileName;
	int64_t totalSize, receiveSize;
};

class zClient : public QWidget {
Q_OBJECT
public:
	explicit zClient(QWidget *parent = nullptr);

	~zClient() override;

private:
	tools::IPPort *ipPort;
	QThread *recThread;
	ClientSend *clientSend;
};


#endif //SUMARY_CLIENT_H
