#include "SetLayer.h"
#include "GlobalVal.h"

USING_NS_CC;

SetLayer::SetLayer():	btnMusic(nullptr),
						btnSound(nullptr),
						bg(nullptr)
{

}

bool SetLayer::init(){
	bool re	=	Layer::init();
	Size winSize	=	Director::getInstance()->getVisibleSize();
	log("init SetLayer");

	LayerColor* lc	=	LayerColor::create(Color4B(225,225,225,128));
	this->addChild(lc,-1);
	lc->setPosition(Point::ZERO);

	bg	=	Sprite::createWithSpriteFrameName("SetLayer.png");
	this->addChild(bg,0);
	bg->setPosition(winSize*0.5);

	Sprite* slotMusic	=	Sprite::createWithSpriteFrameName("SetSlot.png");
	this->addChild(slotMusic,1);
	slotMusic->setPosition(bg->getPosition()+Point(winSize.width*0.17,winSize.height*0.05));
	btnMusic	=	Sprite::createWithSpriteFrameName("SetButton.png");
	btnMusic->setPosition(slotMusic->getPosition());
	this->addChild(btnMusic,2);
	btnMusic->setVisible(playMusic);

	Sprite* slotSound	=	Sprite::createWithSpriteFrameName("SetSlot.png");
	this->addChild(slotSound,1);
	slotSound->setPosition(bg->getPosition()+Point(winSize.width*0.17,winSize.height*0));
	btnSound	=	Sprite::createWithSpriteFrameName("SetButton.png");
	btnSound->setPosition(slotSound->getPosition());
	this->addChild(btnSound,2);
	btnSound->setVisible(playSound);

	return re;
}

bool SetLayer::onTouchBegan(Touch *touch, Event *unused_event){
	log("SetLayer touched.");

	if(!bg->getBoundingBox().containsPoint(touch->getLocation())){
		this->enableSetLayer(false);
		//this->setVisible(false);
		return false;
	}
	log("Touch in box");
	if(btnMusic->getBoundingBox().containsPoint(touch->getLocation())){
		if(playSound)
			PLAY_BUTTONSOUND;
		if(playMusic)
			CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
		else
			CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_THEME);
		
		playMusic	=	!playMusic;
		btnMusic->setVisible(playMusic);
		UserDefault::getInstance()->setBoolForKey(PLAY_MUSIC,playMusic);
	}
	if(btnSound->getBoundingBox().containsPoint(touch->getLocation())){
		if(playSound)
			PLAY_BUTTONSOUND;
// 		if(playSound)
// 			CocosDenshion::SimpleAudioEngine::getInstance()->stopEffect();
		playSound	=	!playSound;
		btnSound->setVisible(playSound);
		UserDefault::getInstance()->setBoolForKey(PLAY_SOUND,playSound);
	}

	return true;
}

void SetLayer::enableSetLayer(bool b){
	if(b){
		auto lis	=	EventListenerTouchOneByOne::create();
		lis->setSwallowTouches(true);
		lis->onTouchBegan	=	CC_CALLBACK_2(SetLayer::onTouchBegan,this);
		_eventDispatcher->addEventListenerWithSceneGraphPriority(lis,this);
	}else{
		_eventDispatcher->removeEventListenersForTarget(this);
	}
}