#ifndef _THEME_LAYER_H_
#define _THEME_LAYER_H_

#include "cocos2d.h"
#include "GameObject/Background.h"
#include "SetLayer.h"

class ThemeLayer:	public cocos2d::Layer
{
public:
	ThemeLayer();

	static cocos2d::Scene* createScene();
	virtual bool init();

	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

	CREATE_FUNC(ThemeLayer);

protected:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *unused_event);
	void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	cocos2d::Sprite* aboutSpr;
	cocos2d::Sprite* helpSpr;
	Background* backSpr;
	cocos2d::Size winSize;
	SetLayer* setLayer;

	void createButtons();
	void showTittle();
	
	void onHelpTouched();
	void onAboutTouched();
	void onSetTouched();
	void moveBackground(float dt);

	void enableTouch();
};

#endif