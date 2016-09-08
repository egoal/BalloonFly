#ifndef _GAME_OVER_H_
#define _GAME_OVER_H_

#include "cocos2d.h"

class GameOverLayer:	public cocos2d::Layer
{
public:
	GameOverLayer():lastScore(0.0){}

	static cocos2d::Scene* createScene(float score);
	void initLayer(float score);

	CREATE_FUNC(GameOverLayer);

protected:
	void onEnterTransitionDidFinish();
	void onExitTransitionDidStart();

private:
	float lastScore;

	void onRestartTouched();
	void onBackTouched();

};
#endif