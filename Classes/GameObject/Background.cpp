#include "Background.h"
#include <iostream>
USING_NS_CC;

Background::Background():v(1.0f),
						 back_1(NULL),
						 back_2(NULL)
{

}

bool Background::init(){
	bool re	=	Layer::init();

	std::cout<<"Init the background."<<std::endl;

	back_1	=	Sprite::createWithSpriteFrameName("Background.png");
	this->addChild(back_1);
	back_1->setAnchorPoint(Point::ZERO);
	back_1->setPosition(Point::ZERO);

	back_2	=	Sprite::createWithSpriteFrameName("Background.png");
	this->addChild(back_2);
	back_2->setAnchorPoint(Point::ZERO);
	back_2->setPosition(back_1->getPositionX()+back_1->getContentSize().width-2,0);

	this->setAnchorPoint(Point::ZERO);
	return re;
}

void Background::move(){
	float x1	=	back_1->getPositionX()-v;
	float x2	=	back_2->getPositionX()-v;
	float w		=	back_1->getContentSize().width;

	if(x1+w < -10){
		x1	=	x2+w-2;
	}
	if(x2+w < -10){
		x2	=	x1+w-2;
	}

	back_1->setPositionX(x1);
	back_2->setPositionX(x2);
}