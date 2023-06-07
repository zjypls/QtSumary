//
// Created by 32725 on 2023/6/6.
//

#ifndef SUMARY_TETRIS_H
#define SUMARY_TETRIS_H
#include <QWidget>
#include <QVector2D>

constexpr int column = 10;
constexpr int row = 20;
constexpr int blockSize = 40;
constexpr int distance = 2;

class zTetris:public QWidget {
public:
	explicit zTetris(QWidget *parent = nullptr);
	~zTetris() override;
protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
private:
	QVector2D index{0, 0};
	bool status[column][row]{true};
	QPainter* painter;
};


#endif //SUMARY_TETRIS_H
