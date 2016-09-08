#include "ThemeLayer.h"
#include "GlobalVal.h"
#include "GameLayer.h"

USING_NS_CC;

ThemeLayer::ThemeLayer():aboutSpr(NULL),
						 helpSpr(NULL),
						 backSpr(NULL),
						 setLayer(nullptr)
{

}

Scene* ThemeLayer::createScene(){
	Scene* sc	=	Scene::create();
	ThemeLayer* ly	=	ThemeLayer::create();
	sc->addChild(ly);

	return sc;
}

bool ThemeLayer::init(){
	bool re	=	Layer::init();

	winSize	=	Director::getInstance()->getWinSize();

	backSpr	=	Background::create();
	this->addChild(backSpr,0);
	backSpr->setPosition(Point::ZERO);
	this->schedule(SEL_SCHEDULE(&ThemeLayer::moveBackground),0.02);

	helpSpr	=	Sprite::createWithSpriteFrameName("HelpPic.png");
	aboutSpr	=	Sprite::createWithSpriteFrameName("About.png");

	this->addChild(helpSpr,10);
	this->addChild(aboutSpr,10);
	aboutSpr->setVisible(false);
	helpSpr->setVisible(false);
	helpSpr->setPosition(winSize*0.5);
	aboutSpr->setAnchorPoint(Point(0,1));
	aboutSpr->setPosition(winSize.width*0.02,winSize.height*0.96);

	if(UserDefault::getInstance()->getBoolForKey(FIRST_TRY,true)){
		UserDefault::getInstance()->setBoolForKey(FIRST_TRY,false);
		onHelpTouched();
	}

	Sprite* doll	=	Sprite::createWithSpriteFrameName("Theme0.png");
	this->addChild(doll,5);
	Vector<SpriteFrame* > frameVec;
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Theme0.png"));
	frameVec.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName("Theme1.png"));
	doll->runAction(RepeatForever::create(Animate::create(Animation::createWithSpriteFrames(frameVec,0.2))));
	doll->setAnchorPoint(Point::ZERO);
	doll->setPosition(winSize.width*0.1,0);
	doll->setRotation(10);
	doll->runAction(RepeatForever::create(Sequence::create(RotateBy::create(2,-20),DelayTime::create(0.2),
														   RotateBy::create(2,20),DelayTime::create(0.2),
														   NULL)));
	doll->setFlippedX(true);
	doll->setScale(0.8);

	createButtons();

	setLayer	=	SetLayer::create();
	this->addChild(setLayer,20);
	setLayer->setPosition(Point::ZERO);
	setLayer->setVisible(false);

	//¿ªÆôÒôÀÖ
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_THEME,true);

	return re;
}

void ThemeLayer::onEnterTransitionDidFinish(){

}

void ThemeLayer::onExitTransitionDidStart(){
	_eventDispatcher->removeEventListenersForTarget(this);
}

bool ThemeLayer::onTouchBegan(Touch *touch, Event *unused_event){
	if(aboutSpr->isVisible()){
		aboutSpr->setVisible(false);
		return true;
	}
	if(helpSpr->isVisible()){
		helpSpr->setVisible(false);
		return true;
	}
	if(setLayer->isVisible()){
		setLayer->setVisible(false);
		return true;
	}
	if(!helpSpr->isVisible() && !aboutSpr->isVisible() && !setLayer->isVisible()){
		Director::getInstance()->replaceScene(TransitionFade::create(1.0,GameLayer::createScene()));
	}

	return true;
}
void ThemeLayer::onTouchMoved(Touch *touch, Event *unused_event){}
void ThemeLayer::onTouchEnded(Touch *touch, Event *unused_event){}

void ThemeLayer::onHelpTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	helpSpr->setScale(0.1);
	helpSpr->setVisible(true);
	helpSpr->runAction(ScaleTo::create(0.5,1.0));
}

void ThemeLayer::onAboutTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	aboutSpr->setVisible(true);
	aboutSpr->setPosition(winSize.width*0.08,winSize.height*0.88);
}

void ThemeLayer::onSetTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	setLayer->setVisible(true);
	setLayer->enableSetLayer(true);
}

void ThemeLayer::createButtons(){
	MenuItemImage* btnHelp	=	MenuItemImage::create("menu/btnHelpN.png","menu/btnHelpS.png",
														CC_CALLBACK_0(ThemeLayer::onHelpTouched,this));
	MenuItemImage* btnSet	=	MenuItemImage::create("menu/btnSetN.png","menu/btnSetS.png",
														CC_CALLBACK_0(ThemeLayer::onSetTouched,this));
	MenuItemImage* btnAbout	=	MenuItemImage::create("menu/btnAboutN.png","menu/btnAboutS.png",
														CC_CALLBACK_0(ThemeLayer::onAboutTouched,this));
	Menu* menu	=	Menu::create(btnHelp,btnSet,btnAbout,NULL);
	this->addChild(menu,8);
	menu->setPosition(Point::ZERO);

	//animation
	btnHelp->setAnchorPoint(Point(0,1));
	btnHelp->setPosition(-winSize.width*0.20,winSize.height*0.98);
	btnSet->setAnchorPoint(Point(0,1));
	btnSet->setPosition(-winSize.width*0.20,winSize.height*0.92);
	btnAbout->setAnchorPoint(Point(0,1));
	btnAbout->setPosition(-winSize.width*0.20,winSize.height*0.86);

	btnHelp->runAction(MoveBy::create(0.6,Point(winSize.width*0.22,0)));
	btnSet->runAction(Sequence::create(DelayTime::create(0.5),
										 MoveBy::create(0.6,Point(winSize.width*0.22,0)),
										 CallFunc::create(CC_CALLBACK_0(ThemeLayer::showTittle,this)),
										 NULL));
	btnAbout->runAction(Sequence::create(DelayTime::create(1.0),
											MoveBy::create(0.6,Point(winSize.width*0.22,0)),
											CallFunc::create(CC_CALLBACK_0(ThemeLayer::enableTouch,this)),
											NULL));
}

void ThemeLayer::showTittle(){
	Sprite* tiSpr	=	Sprite::createWithSpriteFrameName("Tittle.png");
	tiSpr->setScale(0.1);
	this->addChild(tiSpr,6);
	tiSpr->setPosition(winSize.width*0.5,winSize.height*0.8);

	tiSpr->runAction(ScaleTo::create(1.0,1.0));
	tiSpr->runAction(RepeatForever::create(Sequence::create(MoveBy::create(0.5,Point(0,10)),
															DelayTime::create(0.2),
															MoveBy::create(0.5,Point(0,-10)),
															DelayTime::create(0.2),
															NULL)));

}

void ThemeLayer::moveBackground(float dt){
	backSpr->move();
}

void ThemeLayer::enableTouch(){
	auto* eL	=	EventListenerTouchOneByOne::create();
	eL->onTouchBegan	=	CC_CALLBACK_2(ThemeLayer::onTouchBegan,this);
	eL->onTouchMoved	=	CC_CALLBACK_2(ThemeLayer::onTouchMoved,this);
	eL->onTouchEnded	=	CC_CALLBACK_2(ThemeLayer::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eL,this);
}