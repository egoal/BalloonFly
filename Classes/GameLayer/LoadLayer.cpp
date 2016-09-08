#include "LoadLayer.h"
#include "ThemeLayer.h"
#include <iostream>
#include "GlobalVal.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

LoadLayer::LoadLayer(){

}

Scene* LoadLayer::createScene(){
	Scene* sc	=	Scene::create();
	LoadLayer* ly	=	LoadLayer::create();
	sc->addChild(ly);

	return sc;
}

bool LoadLayer::init(){
	bool re	=	Layer::init();

	//载入首选项
	playMusic	=	UserDefault::getInstance()->getBoolForKey(PLAY_MUSIC,true);
	playSound	=	UserDefault::getInstance()->getBoolForKey(PLAY_SOUND,true);
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("FrameCache.plist");
	if(playMusic||playSound)
		loadSoundAndMusic();

	LayerColor* wBack	=	LayerColor::create(Color4B::WHITE);
	Sprite* mark	=	Sprite::createWithSpriteFrameName("Mark.png");
	this->addChild(wBack,-1,100);
	this->addChild(mark,0,200);
	wBack->setPosition(Point::ZERO);
	mark->setPosition(Director::getInstance()->getVisibleSize()*0.5);

	mark->runAction(Sequence::createWithTwoActions(DelayTime::create(1.5),
												 CallFunc::create(CC_CALLBACK_0(LoadLayer::loadingAnimate,this))));

	return re;
}

void LoadLayer::loadingAnimate(){
	static_cast<Sprite*>(getChildByTag(100))->setVisible(false);
	static_cast<Sprite*>(getChildByTag(200))->setVisible(false);

	auto winSize	=	Director::getInstance()->getVisibleSize();

	int i	=	random(1,10);
	char tipFile[20];
	sprintf(tipFile,"Tip (%d).png",i);
	Sprite* tipSpr	=	Sprite::createWithSpriteFrameName(tipFile);
	this->addChild(tipSpr,1);
	tipSpr->setPosition(winSize.width*0.5,winSize.height*0.6);

	Label* loadLbl	=	Label::createWithTTF("Loading...","font/Jack.ttf",48);
	this->addChild(loadLbl,1);
	loadLbl->setPosition(winSize.width*0.7,winSize.height*0.1);

	loadLbl->runAction(Sequence::createWithTwoActions(DelayTime::create(1.5),
													  CallFunc::create(CC_CALLBACK_0(LoadLayer::onLoadFinished,this))));
}

void LoadLayer::onLoadFinished(){
	Director::getInstance()->replaceScene(TransitionFade::create(1.0,ThemeLayer::createScene()));
}

void LoadLayer::loadSoundAndMusic(){
	std::cout<<"now load music"<<std::endl;

	CocosDenshion::SimpleAudioEngine* s	=	CocosDenshion::SimpleAudioEngine::getInstance();

	s->preloadBackgroundMusic(MUSIC_GAME);
	s->preloadBackgroundMusic(MUSIC_THEME);
	s->preloadEffect(SOUND_BUTTON);
	s->preloadEffect(SOUND_BALLOON_FALLEN);
	s->preloadEffect(SOUND_BALLOON_HURTED);
	s->preloadEffect(SOUND_RBIRD);
	s->preloadEffect(SOUND_SBIRD);
	s->preloadEffect(SOUND_TOOLGET);

	std::cout<<"sound loaded."<<std::endl;
}