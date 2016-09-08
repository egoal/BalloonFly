#include "Hero.h"

USING_NS_CC;

const Point bodyAnchor(0.555,0.793);
const Point bodyHurtSize(0.13,0.282);
const Point bodyHurtPos(0,-0.107);
const Point bodyEatSize(0.350,0.644);
const Point bodyEatPos(-0.220,-0.468);
const Point balloonAnchor(0.452,0.291);
const Point balloonSize(0.250,0.445);
const Point balloonPos(-0.125,0.103);

Hero::Hero():bodySpr(NULL),
			 balloonSpr(NULL),
			 linkSpr(NULL),
			 bodyState(Hurted),
			 balloonState(Usual),
			 normalVec(),
			 leakVec(),
			 sunVec(),
			 theadVec(),
			 explodVec(),
			 swingVec()
{

}

Hero* Hero::createHero(){
	Hero* h	=	Hero::create();
	if(h){
		h->initHero();
		return h;
	}
	CC_SAFE_DELETE(h);
	return NULL;
}

void Hero::initHero(){
	linkSpr	=	Sprite::createWithSpriteFrameName("LinkNormal.png");
	this->addChild(linkSpr,0);
	bodySpr	=	Sprite::createWithSpriteFrameName("HeroNormal0.png");
	this->addChild(bodySpr,1);
	bodySpr->setAnchorPoint(bodyAnchor);
	balloonSpr	=	Sprite::createWithSpriteFrameName("BalloonNormal.png");
	this->addChild(balloonSpr,1);
	balloonSpr->setAnchorPoint(balloonAnchor);
	
	initAnimation();

	constructHero();
	setBodyState(Normal);
	setBalloonState(Usual);
}

void Hero::constructHero(){
	//linkSpr->setPosition(getPosition());
	bodySpr->setPosition(linkSpr->getPosition()+Point(0,-linkSpr->getBoundingBox().size.height*0.5));
	balloonSpr->setPosition(linkSpr->getPosition()+Point(0,linkSpr->getBoundingBox().size.height*0.5));

}

void Hero::initAnimation(){
	normalVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroNormal0.png"));
	normalVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroNormal1.png"));
	sunVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroSun0.png"));
	sunVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroSun1.png"));
	theadVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroThead0.png"));
	theadVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroThead1.png"));

	leakVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonLeak0.png"));
	leakVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonLeak1.png"));
	explodVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonExplode0.png"));
	explodVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonExplode1.png"));
	explodVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonExplode2.png"));

	swingVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("LinkSwing0.png"));
	swingVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("LinkSwing1.png"));

}

void Hero::setBodyState(BodyState s){
	if(bodyState	==	s)
		return;

	bodyState	=	s;
	bodySpr->stopAllActions();
	switch (bodyState)
	{
	case Hero::Normal:
		bodySpr->runAction(RepeatForever::create(Animate::create(
			Animation::createWithSpriteFrames(normalVec,0.2))));
		break;
	case Hero::Sun:
		bodySpr->runAction(RepeatForever::create(Animate::create(
			Animation::createWithSpriteFrames(sunVec,0.2))));
		break;
	case Hero::THead:
		bodySpr->runAction(RepeatForever::create(Animate::create(
			Animation::createWithSpriteFrames(theadVec,0.2))));
		break;
	case Hero::Hurted:
		bodySpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("HeroHurted.png"));
		bodySpr->runAction(Sequence::create(Blink::create(1,2),
											//CallFunc::create(CC_CALLBACK_0(Hero::fromHurtedToNormal,this)),
											CallFunc::create(CC_CALLBACK_0(Hero::setBodyState,this,Normal)),
											NULL));
		break;
	default:
		break;
	}
}
void Hero::fromHurtedToNormal(){
	
}

void Hero::setBalloonState(BalloonState s){
	if(balloonState	==	s)
		return;

	balloonState	=	s;
	balloonSpr->stopAllActions();
	switch (balloonState)
	{
	case Hero::Usual:
		balloonSpr->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("BalloonNormal.png"));
		break;
	case Hero::Leak:
		balloonSpr->runAction(RepeatForever::create(Animate::create(
			Animation::createWithSpriteFrames(leakVec,0.2))));
		break;
	case Hero::Explod:
		balloonSpr->runAction(Sequence::create(Animate::create(Animation::createWithSpriteFrames(explodVec,0.15)),
											   CallFunc::create(CC_CALLBACK_0(Hero::heroBelowAction,this)),
											   NULL));
		break;
	default:
		break;
	}
}
void Hero::heroBelowAction(){
	balloonSpr->setVisible(false);
	linkSpr->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(swingVec,0.2))));

	this->runAction(MoveBy::create(1.0,Point(0,-Director::getInstance()->getVisibleSize().height)));
}

void Hero::strench(float s){
	float l1	=	linkSpr->getBoundingBox().size.height;
	linkSpr->setScaleY(s);
	float l2	=	linkSpr->getBoundingBox().size.height;

	setPositionY(getPositionY()+(l2-l1)*0.25);

	constructHero();
}

Rect Hero::getBodyBox(){
	return createRect(bodySpr->getBoundingBox().size,bodyHurtPos,bodyHurtSize,bodySpr);
}
Rect Hero::getBalloonBox(){
	return createRect(balloonSpr->getBoundingBox().size,balloonPos,balloonSize,balloonSpr);
}
Rect Hero::getEatBox(){
	return createRect(bodySpr->getBoundingBox().size,bodyEatPos,bodyEatSize,bodySpr);
}

Rect Hero::createRect(Size boundSize,Point pos,Point boxSize,Sprite* spr){
	float x	=	boundSize.width*pos.x;
	float y	=	boundSize.height*pos.y;
	Point lbPos	=	Point(x,y)+getPosition()+spr->getPosition();
	float w	=	boundSize.width*boxSize.x;
	float h	=	boundSize.height*boxSize.y;

	return Rect(lbPos.x,lbPos.y,w,h);
}