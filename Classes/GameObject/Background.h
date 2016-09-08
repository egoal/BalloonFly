#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "cocos2d.h"

class Background:	public cocos2d::Layer
{
public:
	Background();

	virtual bool init();
	CREATE_FUNC(Background);

	void move();
	void setMoveSpeed(float iV){ v	=	iV;}

private:
	float v;
	cocos2d::Sprite* back_1;
	cocos2d::Sprite* back_2;
};

#endif