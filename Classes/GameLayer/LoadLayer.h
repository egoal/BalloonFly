#ifndef _LOAD_LAYER_H_
#define _LOAD_LAYER_H_

#include "cocos2d.h"

class LoadLayer:	public cocos2d::Layer
{
public:
	LoadLayer();
	CREATE_FUNC(LoadLayer);

	static cocos2d::Scene* createScene();
	virtual bool init();

private:
	void loadSoundAndMusic();

	void loadingAnimate();
	void onLoadFinished();
};

#endif