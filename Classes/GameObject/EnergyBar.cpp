#include "EnergyBar.h"

USING_NS_CC;

EnergyBar::EnergyBar():cVal(100.0),
					   markSpr(NULL),
					   liquidSpr(NULL),
					   boundSpr(NULL)
{

}

bool EnergyBar::init(){
	bool re	=	Layer::init();

	Size winSize	=	Director::getInstance()->getVisibleSize();

	markSpr	=	Sprite::createWithSpriteFrameName("BarMark.png");
	this->addChild(markSpr);
	liquidSpr	=	Sprite::createWithSpriteFrameName("BarLiquid.png");
	this->addChild(liquidSpr);
	boundSpr	=	Sprite::createWithSpriteFrameName("BarBound.png");
	this->addChild(boundSpr,1);

	boundSpr->setAnchorPoint(Point::ZERO);
	boundSpr->setPosition(winSize.width*0.07,winSize.height*0.15);
	liquidSpr->setAnchorPoint(Point::ZERO);
	liquidSpr->setPosition(boundSpr->getPosition());
	markSpr->setPosition(boundSpr->getPositionX()*0.6,boundSpr->getPositionY()+boundSpr->getContentSize().height*0.5);
	
	markSpr->runAction(RepeatForever::create(Sequence::create(ScaleTo::create(0.3,1.1),DelayTime::create(0.1),
															  ScaleTo::create(0.3,0.9),DelayTime::create(0.1),
															  NULL)));

	return re;
}

void EnergyBar::updateBar(){
	cVal	=	cVal>100.0?100.0:cVal;
	cVal	=	cVal<0.0?0.0:cVal;

	liquidSpr->setScaleY(cVal/100.0);
}