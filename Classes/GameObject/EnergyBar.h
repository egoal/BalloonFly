//直接默认为1~100
#ifndef _ENERGY_BAR_H_
#define _ENERGY_BAR_H_

#include "cocos2d.h"

class EnergyBar:	public cocos2d::Layer
{
public:
	EnergyBar();

	virtual bool init();
	CREATE_FUNC(EnergyBar);
	
	float getPercentage(){return cVal;}
	void setPercentage(float c){ cVal	=	c;updateBar();}

private:
	float cVal;
	cocos2d::Sprite* markSpr;
	cocos2d::Sprite* liquidSpr;
	cocos2d::Sprite* boundSpr;

	void updateBar();

};
#endif