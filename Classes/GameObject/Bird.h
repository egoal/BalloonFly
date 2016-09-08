#ifndef _BIRD_H_
#define _BIRD_H_

#include "cocos2d.h"

class Bird:	public cocos2d::Sprite
{
public:
	Bird():isWarm(false),birdType(RBird),vx(0.0),vy(0.0),angle(0.0),
		   sy(0.0f),birdName("")
	{}
	enum Type{
		RBird,
		SBird
	};

	static Bird* createBird(Type t);

	void initBird();

	void upsideDown();
	void setBirdType(Type t){birdType	=	t;}
	Type getBirdType(){ return birdType; }
	cocos2d::Rect getHitBox();
	cocos2d::Rect getBoundBox(){
		cocos2d::Size s	=	this->getBoundingBox().size;
		return cocos2d::Rect(getPositionX()-s.width*0.4,getPositionY()-s.height*0.3,
							 s.width*0.8,s.height*0.6);
	}
	void move();
	bool isWarm;

	CREATE_FUNC(Bird);

	void showBelowAnimation();

private:
	Type birdType;	
	float vx,vy;
	float angle;
	float sy;
	std::string birdName;
};
#endif