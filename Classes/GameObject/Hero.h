#ifndef _HERO_H_
#define _HERO_H_

#include "cocos2d.h"

class Hero:	public cocos2d::Node
{
public:
	Hero();

	enum BodyState{
		Normal,
		Sun,
		THead,
		Hurted
	};
	enum BalloonState{
		Usual,
		Leak,
		Explod
	};

	static Hero* createHero();
	void initHero();

	CREATE_FUNC(Hero);

	void setBodyState(BodyState s);
	void setBalloonState(BalloonState s);
	void strench(float s);
	void scaeleBalloon(float s){
		balloonSpr->setScale(s);
	}

	cocos2d::Rect getBodyBox();
	cocos2d::Rect getBalloonBox();
	cocos2d::Rect getEatBox();

	BodyState bodyState;
	BalloonState balloonState;
private:
	cocos2d::Sprite* bodySpr;
	cocos2d::Sprite* balloonSpr;
	cocos2d::Sprite* linkSpr;

	cocos2d::Vector<cocos2d::SpriteFrame* > normalVec;
	cocos2d::Vector<cocos2d::SpriteFrame* > sunVec;
	cocos2d::Vector<cocos2d::SpriteFrame* > theadVec;
	cocos2d::Vector<cocos2d::SpriteFrame* > leakVec;
	cocos2d::Vector<cocos2d::SpriteFrame* > explodVec;
	cocos2d::Vector<cocos2d::SpriteFrame* > swingVec;

	void constructHero();
	void initAnimation();
	void fromHurtedToNormal();
	void heroBelowAction();

	cocos2d::Rect createRect(cocos2d::Size boundSize,cocos2d::Point pos,cocos2d::Point boxSize,cocos2d::Sprite* spr);
};

#endif // !_HERO_H_
