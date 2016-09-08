#ifndef _SET_LAYER_H_
#define _SET_LAYER_H_

#include "cocos2d.h"

class SetLayer:	public cocos2d::Layer
{
public:
	SetLayer();

	virtual bool init();
	CREATE_FUNC(SetLayer);

	void enableSetLayer(bool b);

protected:
	bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *unused_event);

private:
	cocos2d::Sprite* bg;
	cocos2d::Sprite* btnMusic;
	cocos2d::Sprite* btnSound;

};

#endif