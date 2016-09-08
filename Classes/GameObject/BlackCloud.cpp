#include "BlackCloud.h"

USING_NS_CC;

void BlackCloud::move(){
	setPositionX(getPositionX()+v);
}

Rect BlackCloud::getHitBox(){
	Size s	=	getBoundingBox().size;

	return Rect(getPositionX()-s.width*0.4,getPositionY()-s.height*0.4,s.width*0.8,s.height*0.8);
}

bool BlackCloud::init(){
	bool re	=	Sprite::init();

	int i	=	random(0,100)>50?0:1;
	
	char cStr[30];
	sprintf_s(cStr,"BlackCloud%d.png",i);
	this->initWithSpriteFrameName(cStr);
	this->runAction(RepeatForever::create(Sequence::create(ScaleBy::create(0.3,1.1),
														   DelayTime::create(0.2),
														   ScaleBy::create(0.3,0.9),
														   DelayTime::create(0.2),
														   NULL)));

	return re;
}