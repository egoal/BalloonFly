#include "GameLayer.h"
#include "GameObject/Background.h"
#include "GameObject/EnergyBar.h"
#include "PauseLayer.h"
#include "GameOverLayer.h"
#include "GlobalVal.h"

USING_NS_CC;

GameLayer::GameLayer():bg(NULL),
					   bar(NULL),
					   hero(NULL),
					   vx(0.0),
					   vy(0.0),
					   vleak(0.6),
					   vinput(10),
					   score(0.0),
					   HeroInCloud(false),
					   cloudVec(),
					   toolVec(),
					   birdVec(),
					   linkScale(1.0),
					   nTheadTime(0),
					   scoreLbl(nullptr),
					   isPressing(false),
					   vhold(0.5),
					   water_2(nullptr),
					   water_1(nullptr)
{

}

Scene* GameLayer::createScene(){
	Scene* sc	=	Scene::create();
	GameLayer* ly	=	GameLayer::create();
	sc->addChild(ly);

	return sc;
}

bool GameLayer::init(){
	bool re	=	Layer::init();

	winSize	=	Director::getInstance()->getVisibleSize();

	//添加背景
	bg	=	Background::create();
	this->addChild(bg,0);
	bg->setPosition(Point::ZERO);
	
	//UI
	bar	=	EnergyBar::create();
	this->addChild(bar,10);
	bar->setPosition(Point::ZERO);
	bar->setPercentage(50.0);

	char scoreStr[40];
	sprintf_s(scoreStr,"SCORE: %.0f",score);
	scoreLbl	=	Label::createWithTTF(scoreStr,"font/Jack.ttf",60);//计分板
	this->addChild(scoreLbl,10);
	scoreLbl->setAnchorPoint(Point(1.0,1.0));
	scoreLbl->setPosition(winSize*0.98);
	scoreLbl->setTextColor(Color4B::BLACK);

	MenuItemImage* pauseSpr	=	MenuItemImage::create("menu/btnPauseN.png","menu/btnPauseS.png",
												      CC_CALLBACK_0(GameLayer::onPauseTouched,this));
	Menu* menu	=	Menu::create(pauseSpr,NULL);
	this->addChild(menu,10);
	menu->setPosition(Point::ZERO);
	pauseSpr->setAnchorPoint(Point(0,1));
	pauseSpr->setPosition(winSize.width*0.02,winSize.height*0.98);

	//英雄
	hero	=	Hero::createHero();
	this->addChild(hero,1);
	hero->setPosition(winSize.width*0.2,winSize.height*0.5);

	water_1	=	Sprite::createWithSpriteFrameName("waterline.png");
	this->addChild(water_1,3);
	water_1->setAnchorPoint(Point::ZERO);
	water_1->setPosition(Point::ZERO);

	water_2	=	Sprite::createWithSpriteFrameName("waterline.png");
	this->addChild(water_2,3);
	water_2->setAnchorPoint(Point::ZERO);
	water_2->setPosition(Point::ZERO+Point(water_1->getContentSize().width-2,0));

	//开启音乐
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(MUSIC_GAME,true);

	//测试
	//testNode	=	DrawNode::create();
	//this->addChild(testNode,100);

	return re;
}

void GameLayer::onEnterTransitionDidFinish(){
	//添加响应
	auto eL	=	EventListenerTouchOneByOne::create();
	eL->onTouchBegan	=	CC_CALLBACK_2(GameLayer::onTouchBegan,this);
	eL->onTouchMoved	=	CC_CALLBACK_2(GameLayer::onTouchMoved,this);
	eL->onTouchEnded	=	CC_CALLBACK_2(GameLayer::onTouchEnded,this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(eL,this);
	//开始循环
	this->schedule(SEL_SCHEDULE(&GameLayer::gameStep),0.02);

	this->schedule(SEL_SCHEDULE(&GameLayer::createClouds),15+CCRANDOM_0_1()*10,CC_REPEAT_FOREVER,10);
	this->schedule(SEL_SCHEDULE(&GameLayer::createTools),30+10*CCRANDOM_0_1(),CC_REPEAT_FOREVER,20);
	this->schedule(SEL_SCHEDULE(&GameLayer::createBirds),2+CCRANDOM_0_1()*1);

	//this->schedule(SEL_SCHEDULE(&GameLayer::drawTest),0.02);
}

void GameLayer::onExitTransitionDidStart(){
	_eventDispatcher->removeEventListenersForTarget(this);
	this->unscheduleAllSelectors();
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
}

/************************************************************************/
/* 循环                                                                     */
/************************************************************************/
void GameLayer::gameStep(float dt){
	bg->move();

	bar->setPercentage(bar->getPercentage()-vleak);

	score	+=	0.04;
	char scoreStr[40];
	sprintf_s(scoreStr,"SCORE: %.0f",score);
	scoreLbl->setString(scoreStr);

	moveHero();
	moveClouds();
	moveBirds();
	moveTools();
	moveWater();

	hitTestBirdWithHero();
	hitTestCloudWithHero();
	hitTestToolWithHero();

}

void GameLayer::moveHero(){
	//0.3~1.7
	hero->scaeleBalloon((bar->getPercentage()-50.0)/50.0*0.7+1.0);

	vy	=	(bar->getPercentage()-50.0)/50.0*8.0;
	Point heroPos	=	hero->getPosition();
	if(heroPos.x < -winSize.width*0.05 || heroPos.y <= winSize.height*0.08)
		gameOver();
	if(!HeroInCloud)
		vx	=	heroPos.x<winSize.width*0.2?2.0:0.0;

	hero->setPosition(heroPos+Point(vx,vy));

	//雷电时间
	if(nTheadTime>0){
		--nTheadTime;
	}
	if(isPressing){
		bar->setPercentage(bar->getPercentage()+vhold);
	}
	if(hero->bodyState	==	Hero::THead && nTheadTime <= 0)
		hero->setBodyState(Hero::Normal);
}

void GameLayer::createClouds(float dt){
	int mount	=	CCRANDOM_0_1()>0.7?2:1;
	for(int i=0;i<mount;++i){
		float x	=	winSize.width*(1.1+0.3*CCRANDOM_0_1());
		float y;
		float onY	=	random(0,100);
		if(onY<40)
			y	=	winSize.height*(0.1+0.3*CCRANDOM_0_1());
		else if(onY < 60)
			y	=	winSize.height*(0.4+0.2*CCRANDOM_0_1());
		else
			y	=	winSize.height*(0.6+0.3*CCRANDOM_0_1());
		float scale	=	0.8+CCRANDOM_0_1()*0.4;
		float vc	=	-(1.5+CCRANDOM_0_1()*2.0);

		BlackCloud* bc	=	BlackCloud::create();
		bc->setScale(scale);
		bc->setPosition(x,y);
		bc->setStaticVelocity(vc);
		bc->resetVelocity();
		this->addChild(bc,2);
		cloudVec.pushBack(bc);
	}

}
void GameLayer::moveClouds(){
	for(int i = cloudVec.size()-1;i>=0;--i){
		BlackCloud* bc	=	cloudVec.at(i);
		bc->move();
		if(bc->getPositionX() < -winSize.width*0.2){
			bc->removeFromParent();
			cloudVec.erase(i);
		}
	}
}

void GameLayer::createTools(float dt){
	SpecialTool::Type t;
	float onTool	=	random(0,100);
	if(onTool<40)
		t	=	SpecialTool::Water;
	else if(onTool<70)
		t	=	SpecialTool::Thead;
	else
		t	=	SpecialTool::Sun;

	SpecialTool* st	=	SpecialTool::createTool(t);
	st->setPosition(winSize.width*1.1,winSize.height*(0.1+0.8*CCRANDOM_0_1()));

	this->addChild(st,1);
	toolVec.pushBack(st);
}
void GameLayer::moveTools(){
	for (int i=toolVec.size()-1;i>=0;--i){
		SpecialTool* st	=	toolVec.at(i);
		st->setPositionX(st->getPositionX()-2.0);

		if (st->getPositionX() < -winSize.width*0.1){
			st->removeFromParent();
			toolVec.erase(i);
		}
	}
}

void GameLayer::createBirds(float dt){
	float x	=	winSize.width*(1.1+0.2*CCRANDOM_0_1());
	float y	=	winSize.height*(0.1+CCRANDOM_0_1()*0.9);
	Bird::Type t	=	CCRANDOM_0_1()>0.7?Bird::RBird:Bird::SBird;
	float s	=	0.9+CCRANDOM_0_1()*0.2;

	Bird* bd	=	Bird::createBird(t);
	this->addChild(bd,1);
	bd->setPosition(x,y);
	bd->setScale(s);

	birdVec.pushBack(bd);
}

void GameLayer::moveBirds(){
	for(int i=birdVec.size()-1;i>=0;--i){
		Bird* b	=	birdVec.at(i);
		b->move();
		if(b->getPositionY() >winSize.height || b->getPositionY() <winSize.height*0.05)
			b->upsideDown();
		if(b->getPositionX() < -winSize.width*0.1){
			b->removeFromParent();
			birdVec.erase(i);
		}
	}
}

void GameLayer::gameOver(){
	if(playSound)
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BALLOON_FALLEN);
	Director::getInstance()->replaceScene(GameOverLayer::createScene(score));
}

void GameLayer::moveWater(){
	float w		=	water_1->getContentSize().width;
	float x1	=	water_1->getPositionX()-2.0;
	float x2	=	water_2->getPositionX()-2.0;
	x1	=	(x1+w)>0.0?x1:(water_2->getPositionX()+w-2);
	x2	=	(x2+w)>0.0?x2:(water_1->getPositionX()+w-2);

	water_1->setPositionX(x1);
	water_2->setPositionX(x2);
}

/************************************************************************/
/* 碰撞                                                                     */
/************************************************************************/
void GameLayer::hitTestCloudWithHero(){
	int flag	=	0;
	for(int i = 0;i<cloudVec.size();++i){
		BlackCloud* bc	=	cloudVec.at(i);

		if(bc->getHitBox().intersectsRect(hero->getEatBox()) || 
			bc->getHitBox().intersectsRect(hero->getBalloonBox())){
				++flag;
				vx	=	bc->getStaticVelocity()*0.5;
				bc->setSpeed(vx*1.2);
		}else{
			bc->resetVelocity();
		}
	}
	HeroInCloud	=	(flag==0)?false:true;
}

void GameLayer::hitTestBirdWithHero(){
	for(int i=birdVec.size()-1;i>=0;--i){
		Bird* b	=	birdVec.at(i);

		if(b->isWarm)
			continue;

		bool touchBird	=	b->getBoundBox().intersectsRect(hero->getBalloonBox()) ||
							b->getBoundBox().intersectsRect(hero->getEatBox());
		if(!touchBird)
			continue;
		else{
			bool hitBalloon;
			bool hitBody;
			switch (hero->bodyState){
			case Hero::Sun:
				b->showBelowAnimation();
				birdVec.erase(i);
				hero->setBodyState(Hero::Normal);
				hero->runAction(Blink::create(1,2));
				break;
			case Hero::THead:
				b->showBelowAnimation();
				birdVec.erase(i);
				break;
			case Hero::Normal:
				hitBalloon	=	b->getHitBox().intersectsRect(hero->getBalloonBox());
				hitBody	=	b->getHitBox().intersectsRect(hero->getBodyBox());
				if(hitBalloon){
					b->isWarm	=	true;
					if(hero->balloonState	==	Hero::Usual){
						if(playSound)
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BALLOON_HURTED);
						hero->setBalloonState(Hero::Leak);
						vleak	*=	1.5;
					}else if(hero->balloonState	==	Hero::Leak){
						if(playSound)
							CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_BALLOON_HURTED);
						hero->setBalloonState(Hero::Explod);
					}
				}else if(hitBody){
					b->isWarm	=	true;
					hero->setBodyState(Hero::Hurted);
					vinput	*=	0.85;
				}
				break;
			default:
				break;
			}
		}
	}
}

void GameLayer::hitTestToolWithHero(){
	for(int i=0;i<toolVec.size();++i){
		SpecialTool* st	=	toolVec.at(i);
		if(st->getEatBox().intersectsRect(hero->getEatBox()) && st->isVisible()){
			if(playSound)
				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(SOUND_TOOLGET);
			st->setVisible(false);
			switch (st->getToolType())
			{
			case SpecialTool::Sun:
				hero->setBodyState(Hero::Sun);
				break;
			case SpecialTool::Thead:
				nTheadTime	=	500;
				hero->setBodyState(Hero::THead);
				break;
			case SpecialTool::Water:
				onWaterEaten();
				break;
			default:
				break;
			}
			
		}
	}
}
void GameLayer::onWaterEaten(){
	this->schedule(SEL_SCHEDULE(&GameLayer::createRain),0.4,10,0.0);//0.4s×10

}
void GameLayer::createRain(float dt){
	for(int i = 0; i<10;++i){
		float s	=	0.9+CCRANDOM_0_1()*0.2;
		float x	=	winSize.width*(CCRANDOM_0_1());
		float y	=	winSize.height*(1.1+CCRANDOM_0_1()*0.4);

		Sprite* water	=	Sprite::createWithSpriteFrameName("WaterAttack.png");
		water->setScale(s);
		water->setPosition(x,y);
		this->addChild(water,1);

		water->runAction(Sequence::create(MoveBy::create(1.5,Point(0,-winSize.height*1.5)),
										  RemoveSelf::create(),
										  NULL));
	}
	for(int i	=	birdVec.size()-1;i>=0;--i){
		Bird* b	=	birdVec.at(i);
		if(b->getPositionX() < winSize.width){
			b->showBelowAnimation();
			birdVec.erase(i);
		}
	}
}

/************************************************************************/
/* 响应                                                                     */
/************************************************************************/
bool GameLayer::onTouchBegan(Touch *touch, Event *unused_event){
	if(hero->getPositionY() > winSize.height*0.9)
		return true;

	bar->setPercentage(bar->getPercentage()+vinput);

	isPressing	=	true;

	return true;
}
void GameLayer::onTouchMoved(Touch *touch, Event *unused_event){
	float s	=	(touch->getLocation().y - touch->getStartLocation().y)/(0.3*winSize.height);
	s	=	s>1.0?1.0:s;
	s	=	s<-1.0?-1.0:s;
	//0.5~1.8;
	linkScale	+=	s*0.5;
	linkScale	=	linkScale<0.5?0.5:linkScale;
	linkScale	=	linkScale>1.8?1.8:linkScale;

	hero->strench(linkScale);

}
void GameLayer::onTouchEnded(Touch *touch, Event *unused_event){
	isPressing	=	false;
}

void GameLayer::onPauseTouched(){
	if(playSound)
		PLAY_BUTTONSOUND;
	if(playMusic)
		CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	RenderTexture* rt	=	RenderTexture::create(winSize.width,winSize.height);
	rt->retain();
	rt->begin();
	Director::getInstance()->getRunningScene()->visit();
	rt->end();

	Director::getInstance()->pushScene(PauseLayer::createScene(rt));
}

//测试
/*
void GameLayer::drawTest(float dt){
// 	log("Vec Size: ");
// 	log("toolVec: %d",toolVec.size());
// 	log("birdVec: %d",birdVec.size());
// 	log("cloudVec: %d",cloudVec.size());
	testNode->clear();
	drawRect(hero->getBalloonBox());
	drawRect(hero->getEatBox());
	drawRect(hero->getBodyBox());
	for(int i=0;i<birdVec.size();++i){
		drawRect(birdVec.at(i)->getHitBox());
		drawRect(birdVec.at(i)->getBoundBox());
	}
	for(int i=0;i<toolVec.size();++i)
		drawRect(toolVec.at(i)->getEatBox());
	for(int i=0;i<cloudVec.size();++i){
		drawRect(cloudVec.at(i)->getHitBox());
	}
}
void GameLayer::drawRect(Rect r){
	testNode->drawRect(Point(r.getMinX(),r.getMinY()),Point(r.getMaxX(),r.getMaxY()),Color4F::RED);
}
*/