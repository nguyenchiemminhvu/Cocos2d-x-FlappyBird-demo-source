#include "SplashScene.h"
#include "Defination.h"
#include "MainMenuScene.h"
#include "SimpleAudioEngine.h"

Scene* SplashScene::createScene()	{
	auto scene = Scene::create();
	auto layer = SplashScene::create();
	scene->addChild(layer);
	return scene;
}


bool SplashScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	//load sound
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( "Sounds/Hit.mp3" );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( "Sounds/Point.mp3" );
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect( "Sounds/Wing.mp3" );

	this->scheduleOnce( schedule_selector(SplashScene::goToMainMenuScene), DISPLAY_TIME_SPLASH_SCENE );

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	auto background = Sprite::create("FlappyResources/V_Black.jpg");
	background->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2));

	this->addChild(background);

	return true;
}


void SplashScene::goToMainMenuScene(float t)	{
	Director::getInstance()->replaceScene(TransitionFade::create(TRAINSITION_TIME, MainMenuScene::createScene()));
}