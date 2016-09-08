#include "Bird.h"
#include "GlobalVal.h"

USING_NS_CC;

#define PI 3.1415926

const Point RBirdSize(0.138,0.338);
const Point RBirdPos(-0.457,-0.200);
const Point SBirdSize(0.245,0.2);
const Point SBirdPos(-0.420,0);
const Point SBirdHitPos(-0.397,0);

Bird* Bird::createBird(Type t){
	Bird* b	=	Bird::create();
	b->setBirdType(t);
	b->initBird();

	return b;
}

void Bird::initBird(){
	
	switch (birdType)
	{
	case Bird::RBird:
		birdName	=	"RBird";
		vx	=	-(4.0+CCRANDOM_0_1()*2.0);
		vy	=	3.0+CCRANDOM_0_1()*12;
		break;
	case Bird::SBird:
		birdName	=	"SBird";
		vx	=	-(4.0+CCRANDOM_0_1()*2.0);
		vy	=	-3+CCRANDOM_0_1()*6.0;
		break;
	default:
		break;
	}
	Vector<SpriteFrame* > frameVec;
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(birdName+"Normal0.png"));
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(birdName+"Normal1.png"));

	initWithSpriteFrame(frameVec.front());
	runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frameVec,0.2)	)));

	if(birdType	==	SBird){
		angle	=	atan(vy/(-vx));
		float rangle	=	angle/PI*180.0;
		runAction(RotateBy::create(0.0,rangle));
	}

}

void Bird::move(){
	switch (birdType)
	{
	case Bird::RBird:
		//sy	+=	vy;
		sy	+=	vy;
		vy	-=	sy*(0.008+0.004*CCRANDOM_0_1());
		setPosition(getPosition()+Point(vx,vy));
		break;
	case Bird::SBird:
		setPosition(getPosition()+Point(vx,vy));
		break;
	default:
		break;
	}
}

void Bird::showBelowAnimation(){
	if(playSound){
		switch (birdType)
		{
		case Bird::RBird:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_RBIRD);
			break;
		case Bird::SBird:
			CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_SBIRD);
			break;
		default:
			break;
		}
	}
	this->stopAllActions();
	Size winSize	=	Director::getInstance()->getVisibleSize();
	setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(birdName+"Hurted.png"));
	this->runAction(RepeatForever::create(RotateBy::create(0.5,180)));
	this->runAction(Sequence::create(JumpBy::create(0.5,Point(winSize.width*0.2,0),winSize.height*0.05,1),
					//JumpBy::create(2.0,Point(winSize.width*0.3,-winSize.height*1.2),winSize.height*0.2,1),
					MoveBy::create(2.0,Point(winSize.width*0.15,-winSize.height*1.0)),
					RemoveSelf::create(),NULL));
}

void Bird::upsideDown(){
	vy	*=	-1;
	if(birdType	==	SBird){
		angle	=	atan(vy/(-vx));
		float rangle	=	2*angle/PI*180.0;
		runAction(RotateBy::create(0.3,rangle));
	}
}

Rect Bird::getHitBox(){
	float w,h,x,y;
	Size s	=	getBoundingBox().size;
	switch (birdType)
	{
	case Bird::RBird:
		x	=	getPositionX()+s.width*RBirdPos.x;
		y	=	getPositionY()+s.height*RBirdPos.y;
		w	=	s.width*RBirdSize.x;
		h	=	s.height*RBirdSize.y;
		break;
	case Bird::SBird:
// 		x	=	getPositionX()+s.width*SBirdPos.x;
// 		y	=	getPositionY()+s.height*SBirdPos.y;
// 		w	=	s.width*SBirdSize.x;
// 		h	=	s.height*SBirdSize.y;
		x	=	getPositionX()+s.width*SBirdHitPos.x*cos(angle);
		y	=	getPositionY()+s.width*SBirdHitPos.x*sin(-angle);
		w	=	20;
		h	=	20;
		break;
	default:
		break;
	}

	return Rect(x,y,w,h);
}