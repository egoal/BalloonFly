#include "GameOverLayer.h"
#include "GameLayer.h"
#include "ThemeLayer.h"
#include "GlobalVal.h"

USING_NS_CC;

Scene* GameOverLayer::createScene(float ls){
	Scene* sc	=	Scene::create();
	GameOverLayer* ly	=	GameOverLayer::create();
	ly->initLayer(ls);
	sc->addChild(ly);

	return sc;
}

void GameOverLayer::initLayer(float ls){
	lastScore	=	ls;

	Size winSize	=	Director::getInstance()->getVisibleSize();

	MenuItemImage* restartBtn	=	MenuItemImage::create("menu/btnRestartN.png","menu/btnRestartS.png",
		CC_CALLBACK_0(GameOverLayer::onRestartTouched,this));
	MenuItemImage* backBtn	=	MenuItemImage::create("menu/btnBackN.png","menu/btnBackS.png",
		CC_CALLBACK_0(GameOverLayer::onBackTouched,this));
	Menu* menu	=	Menu::create(restartBtn,backBtn,NULL);
	this->addChild(menu,10);
	menu->setPosition(Point::ZERO);
	backBtn->setAnchorPoint(Point(0,1));
	backBtn->setPosition(winSize.width*0.02,winSize.height*0.98);
	restartBtn->setPosition(winSize.width*0.5,winSize.height*0.3);
	restartBtn->setScale(1.5);

	Sprite* bgSpr	=	Sprite::createWithSpriteFrameName("Background.png");
	this->addChild(bgSpr,-1);
	bgSpr->setPosition(Point::ZERO);
	bgSpr->setAnchorPoint(Point::ZERO);

	Sprite* dftSpr	=	Sprite::createWithSpriteFrameName("DefeatedPic.png");
	this->addChild(dftSpr,0);
	dftSpr->setPosition(winSize.width*0.5,winSize.height*0.5);

	char scoreStr[30];
	sprintf_s(scoreStr,"SCORE: %.0f",lastScore);
	Label* scoreLbl	=	Label::createWithTTF(scoreStr,"font/Jack.ttf",75);
	this->addChild(scoreLbl,5);
	scoreLbl->setTextColor(Color4B::BLACK);
	scoreLbl->setPosition(winSize.width*0.5,winSize.height*0.75);

	float highScore	=	UserDefault::getInstance()->getFloatForKey(HIGHEST_SCORE,0.0);
	if(highScore < lastScore){
		highScore	=	lastScore;
		//new record
		UserDefault::getInstance()->setFloatForKey(HIGHEST_SCORE,highScore);
		Label* recordNew	=	Label::createWithTTF("New Record!","font/Jack.ttf",90);
		this->addChild(recordNew,5);
		recordNew->setPosition(winSize.width*0.5,winSize.height*0.85);
		recordNew->setTextColor(Color4B::BLACK);
	}

	char highStr[30];
	sprintf_s(highStr,"BEST: %.0f",highScore);
	Label* highLbl	=	Label::createWithTTF(highStr,"font/Jack.ttf",45);
	this->addChild(highLbl,5);
	highLbl->setTextColor(Color4B::BLACK);
	highLbl->setPosition(winSize.width*0.5,winSize.height*0.70);


}

void GameOverLayer::onRestartTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	Director::getInstance()->replaceScene(TransitionFade::create(1.0,GameLayer::createScene()));
}

void GameOverLayer::onBackTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	Director::getInstance()->replaceScene(TransitionFade::create(1.0,ThemeLayer::createScene()));
}

void GameOverLayer::onEnterTransitionDidFinish(){
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}
void GameOverLayer::onExitTransitionDidStart(){
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}