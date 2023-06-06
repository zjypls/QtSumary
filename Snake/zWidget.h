//
// Created by 32725 on 2023/6/3.
//

#ifndef SUMARY_ZWIDGET_H
#define SUMARY_ZWIDGET_H

#include <QWidget>
#include <QQueue>
#include <QVector2D>
#include <QPainter>
#include <QLabel>
#include "Snake.h"

class zWidget : public QWidget {
Q_OBJECT
public:
	explicit zWidget(QWidget *parent = nullptr);

	~zWidget() override;
protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	void resizeEvent(QResizeEvent *event) override;
private:
	Snake *snake;
	Food *food;
	QVector2D headPos;
	QVector2D direction;
	QPainter *painter;
	QLabel *sizeLabel;
	QQueue<QVector2D> bodies;
};


#endif //SUMARY_ZWIDGET_H
