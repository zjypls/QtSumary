#include <QApplication>
#include "zWidget.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	zWidget w{};
	w.show();
	return QApplication::exec();
}
