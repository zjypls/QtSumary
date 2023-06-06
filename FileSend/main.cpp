//
// Created by 32725 on 2023/6/3.
//
#include <QApplication>
#include "Client.h"
#include "Server.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	zServer s{};
	s.show();
	zClient w{};
	w.show();
	return QApplication::exec();
}