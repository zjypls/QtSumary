//
// Created by 32725 on 2023/6/3.
//

#ifndef SUMARY_SNAKE_H
#define SUMARY_SNAKE_H

#include <QVector2D>
#include <QQueue>
#include <QTime>
#include <QRandomGenerator>
#include <QKeyEvent>
#include <QPainter>
#define BODY_SIZE 10

class SnakeBody {
public:
	explicit SnakeBody(QVector2D pos);

protected:
	[[nodiscard]] virtual bool isHit(QVector2D _pos);

	friend class Snake;

	QVector2D pos;
};
class Snake;
class Food:public SnakeBody {
	friend class Snake;
public:
	explicit Food(QVector2D pos);
	void Draw(QPainter *painter);
	bool isHit(QVector2D _pos) override;
	void ChangePos(Snake* snake);
	void SetBound(QVector2D _bound);
private:
	QVector2D bound;
	static QRandomGenerator *random;
	bool Show = true;
};

class Snake : public QObject{
	Q_OBJECT
public:
	explicit Snake(QVector2D headPos, QVector2D direction = {-1, 0}, int length = 0);
	void Walk(Food* food);
	void Draw(QPainter *painter);
	void ChangeDirection(QKeyEvent *event);
	bool CheckPos(QVector2D pos);
	[[nodiscard]] inline bool isGameOver() const { return GameOver; }
	inline void SetBound(QVector2D _bound) { bound=_bound; }
	uint32_t GetSize() { return bodies.size(); }
	signals:
	void SizeChanged(int size);
private:
	bool GameOver= false;
	QVector2D headPos, direction, bound;
	QQueue<SnakeBody> bodies;
};


#endif //SUMARY_SNAKE_H
