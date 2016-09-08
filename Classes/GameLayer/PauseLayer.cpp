#include "PauseLayer.h"
#include "ThemeLayer.h"
#include "GameLayer.h"
#include "GlobalVal.h"

USING_NS_CC;

Scene* PauseLayer::createScene(RenderTexture* rt){
	Scene* sc	=	Scene::create();

	Sprite* bgSpr	=	Sprite::createWithTexture(rt->getSprite()->getTexture());
	sc->addChild(bgSpr,0);
	Size winSize	=	Director::getInstance()->getVisibleSize();
	bgSpr->setPosition(winSize*0.5);
	bgSpr->setFlippedY(true);
	bgSpr->setColor(Color3B::GRAY);

	PauseLayer* ly	=	PauseLayer::create();
	sc->addChild(ly,1);

	return sc;
}

bool PauseLayer::init(){
	bool re	=	Layer::init();

	Size winSize	=	Director::getInstance()->getVisibleSize();

	Sprite* pasueSpr	=	Sprite::createWithSpriteFrameName("PausePic.png");
	this->addChild(pasueSpr,0);
	pasueSpr->setPosition(winSize*0.5);

	MenuItemImage* resumeBtn	=	MenuItemImage::create("menu/btnStartN.png","menu/btnStartS.png",
		CC_CALLBACK_0(PauseLayer::onBtnResumeTouched,this));
	MenuItemImage* restartBtn	=	MenuItemImage::create("menu/btnRestartN.png","menu/btnRestartS.png",
		CC_CALLBACK_0(PauseLayer::onBtnRestartTouched,this));
	MenuItemImage* backBtn	=	MenuItemImage::create("menu/btnBackN.png","menu/btnBackS.png",
		CC_CALLBACK_0(PauseLayer::onBtnBackTouched,this));
	Menu* menu	=	Menu::create(resumeBtn,restartBtn,backBtn,NULL);
	this->addChild(menu,10);
	menu->setPosition(Point::ZERO);

	resumeBtn->setPosition(winSize.width*0.63,winSize.height*0.53);
	resumeBtn->setScale(1.5);
	backBtn->setPosition(winSize.width*0.55,winSize.height*0.44);
	restartBtn->setPosition(winSize.width*0.71,winSize.height*0.44);

	return re;
}

void PauseLayer::onBtnResumeTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
	Director::getInstance()->popScene();
}
void PauseLayer::onBtnBackTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0,ThemeLayer::createScene()));
}
void PauseLayer::onBtnRestartTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0,GameLayer::createScene()));
}