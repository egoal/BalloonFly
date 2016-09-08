#ifndef _PAUSE_LAYER_H_
#define _PAUSE_LAYER_H_

#include "cocos2d.h"

class PauseLayer:	public cocos2d::Layer
{
public:
	PauseLayer(){}

	static cocos2d::Scene* createScene(cocos2d::RenderTexture* rt);
	virtual bool init();
	CREATE_FUNC(PauseLayer);

private:
	void onBtnResumeTouched();
	void onBtnBackTouched();
	void onBtnRestartTouched();

};

#endif