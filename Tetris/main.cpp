//
// Created by 32725 on 2023/6/6.
//
#include <QApplication>
#include "Tetris.h"

int main(int argc, char *argv[]){
	QApplication app(argc, argv);
	zTetris w{};
	w.show();
	return QApplication::exec();
}