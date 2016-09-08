#include "SpecialTool.h"

USING_NS_CC;

SpecialTool* SpecialTool::createTool(Type t){
	SpecialTool* st	=	SpecialTool::create();
	if(st){
		st->initTool(t);
		return st;
	}
	CC_SAFE_DELETE(st);
	return NULL;
}

void SpecialTool::initTool(Type t){
	toolType	=	t;

	std::string toolName;
	switch (t)
	{
	case SpecialTool::Sun:
		toolName	=	"sun";
		break;
	case SpecialTool::Thead:
		toolName	=	"Thead";
		break;
	case SpecialTool::Water:
		toolName	=	"Water";
		break;
	default:
		break;
	}

	Vector<SpriteFrame* > frameVec;
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(toolName+"0.png"));
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(toolName+"1.png"));

	this->initWithSpriteFrame(frameVec.front());
	this->runAction(RotateBy::create(0.0,-7.5));
	this->runAction(RepeatForever::create(Sequence::create(RotateBy::create(0.3,15),DelayTime::create(0.2),
														   RotateBy::create(0.3,-15),DelayTime::create(0.2),
														   NULL)));
	this->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frameVec,0.2))));
}

Rect SpecialTool::getEatBox(){
	Size s	=	getBoundingBox().size;

	return Rect(getPositionX()-s.width*0.3,getPositionY()-s.height*0.4,
				s.width*0.6,s.height*0.8);
}

