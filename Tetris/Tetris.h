//
// Created by 32725 on 2023/6/6.
//

#ifndef SUMARY_TETRIS_H
#define SUMARY_TETRIS_H
#include <QWidget>
#include <QVector2D>
#include <QVector>
#include <QPainter>
constexpr short empty=0;
constexpr short full=1;
constexpr int rotateBase=1;
constexpr int column = 10;
constexpr int row = 20;
constexpr int blockSize = 40;
constexpr int distance = 4;

struct ivec2{
	int x,y;
	ivec2(int x=0,int y=0):x(x),y(y){}
	ivec2 operator+(const ivec2& other) const{
		return {x+other.x,y+other.y};
	}
	ivec2 operator-(const ivec2& other) const{
		return {x-other.x,y-other.y};
	}
	ivec2 operator+=(int other){
		return {x+=other,y+=other};
	}
	ivec2 operator-=(int other){
		return {x-=other,y-=other};
	}
	ivec2 operator+=(const ivec2& other){
		return {x+=other.x,y+=other.y};
	}
	ivec2 operator-=(const ivec2& other){
		return {x-=other.x,y-=other.y};
	}
	ivec2 operator*(ivec2 other) const{
		return {x*other.x,y*other.y};
	}
	ivec2 operator~() const{
		return {y,x};
	}
};


struct zShape{
	ivec2 pos[4]{};
	enum class zShapeType{
		eI=0,eO,eT,eS,eZ,eJ,eL
	};
	zShapeType Type;
	explicit zShape(zShapeType type=zShapeType::eI):Type(type){
		switch (type) {
			case zShapeType::eI:
				pos[0]={2,0};pos[1]={3,0};pos[2]={4,0};pos[3]={5,0};
				break;
			case zShapeType::eO:
				pos[0]={3,0};pos[1]={4,0};pos[2]={3,1};pos[3]={4,1};
				break;
			case zShapeType::eT:
				pos[0]={3,0};pos[1]={2,1};pos[2]={3,1};pos[3]={4,1};
				break;
			case zShapeType::eS:
				pos[0]={3,0};pos[1]={4,0};pos[2]={2,1};pos[3]={3,1};
				break;
			case zShapeType::eZ:
				pos[0]={2,0};pos[1]={3,0};pos[2]={3,1};pos[3]={4,1};
				break;
			case zShapeType::eJ:
				pos[0]={2,0};pos[1]={2,1};pos[2]={3,1};pos[3]={4,1};
				break;
			case zShapeType::eL:
				pos[0]={4,0};pos[1]={2,1};pos[2]={3,1};pos[3]={4,1};
				break;
			default:
				throw std::runtime_error("zShapeType error");
		}
	}
	void Draw(QPainter* painter){
		for (auto & po : pos)
			painter->drawRect(po.x*blockSize+distance,po.y*blockSize+distance,blockSize-distance,blockSize-distance);

	}
	void Rotate(){
		//Todo : fix rotate
		return;
		if(Type==zShapeType::eO)
			return;
		static ivec2 temp[4]{};
		std::copy(pos,pos+4,temp);
		for (auto & po : temp){
			po+=((~(po-pos[rotateBase]))*ivec2(1,-1));
			if(po.x<0||po.x>=column||po.y<0||po.y>=row)
				return;
		}
		std::copy(temp,temp+4,pos);
	}
	void Move(int dir,short status[column][row]){
		static ivec2 temp[4]{};
		std::copy(pos,pos+4,temp);
		for (auto & po : temp){
			po.x+=dir;
			if(po.x<0||po.x>=column||status[po.x][po.y]==full)
				return;
		}
		std::copy(temp,temp+4,pos);
	}
	static zShape GenerateShape();
	inline auto& operator[](int index){
		return pos[index];
	}
};
namespace test{
	QString shapeTypeToString(zShape::zShapeType type);
}

class zTetris:public QWidget {
public:
	explicit zTetris(QWidget *parent = nullptr);
	~zTetris() override;
protected:
	void paintEvent(QPaintEvent *event) override;
	void keyPressEvent(QKeyEvent *event) override;
	bool TryFall();
	void CheckDelete();
private:
	short status[column][row]{};
	QPainter* painter;
	zShape shape{zShape::zShapeType::eI};
};


#endif //SUMARY_TETRIS_H
