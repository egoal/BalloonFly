#ifndef _GAME_LAYER_H_
#define _GAME_LAYER_H_

#include "cocos2d.h"
#include "GameObject/Hero.h"
#include "GameObject/BlackCloud.h"
#include "GameObject/SpecialTool.h"
#include "GameObject/Bird.h"

class Background;
class EnergyBar;

class GameLayer:	public cocos2d::Layer
{
public:
	GameLayer();

	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(GameLayer);

protected:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

private:
	Background* bg;
	EnergyBar* bar;
	Hero* hero;
	cocos2d::Vector<BlackCloud* > cloudVec;
	cocos2d::Vector<SpecialTool* > toolVec;
	cocos2d::Vector<Bird* > birdVec;

	cocos2d::Sprite* water_1;
	cocos2d::Sprite* water_2;

	float vx,vy;
	cocos2d::Size winSize;
	float vleak;
	float vinput;
	float vhold;
	bool isPressing;
	bool HeroInCloud;
	float linkScale;

	float score;
	int nTheadTime;
	cocos2d::Label* scoreLbl;

	void gameStep(float dt);
	void moveHero();
	void hitTestCloudWithHero();
	void hitTestBirdWithHero();
	void hitTestToolWithHero();
	void onWaterEaten();
	void createRain(float dt);

	void createClouds(float dt);
	void moveClouds();
	void createTools(float dt);
	void moveTools();
	void createBirds(float dt);
	void moveBirds();
	void moveWater();

	void gameOver();
	void onPauseTouched();

	//≤‚ ‘
	/*
	cocos2d::DrawNode* testNode;
	void drawTest(float dt);
	void drawRect(cocos2d::Rect r);
	*/
};

#endif