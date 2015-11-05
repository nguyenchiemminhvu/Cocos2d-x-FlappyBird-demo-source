#include "SplashScene.h"
#include "Defination.h"
#include "MainMenuScene.h"


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