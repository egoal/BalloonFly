#ifndef _BLACK_CLOUD_H_
#define _BLACK_CLOUD_H_

#include "cocos2d.h"

class BlackCloud:	public cocos2d::Sprite
{
public:
	BlackCloud():v(0.0),staticV(0.0){}
	
	void move();
	cocos2d::Rect getHitBox();
	void resetVelocity(){ v = staticV; }
	void setSpeed(float sv){ v = sv;}
	void setStaticVelocity(float sv){staticV = sv; }
	float getStaticVelocity(){return staticV;}

	virtual bool init();
	CREATE_FUNC(BlackCloud);

private:
	float staticV;
	float v;
	
};

#endif