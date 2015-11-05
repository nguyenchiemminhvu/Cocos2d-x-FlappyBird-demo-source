#include "PauseScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* PauseScene::createScene()	{
	auto scene = Scene::create();
	auto layer = PauseScene::create();
	scene->addChild(layer);
	return scene;
}


bool PauseScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//create background for pause scene
	auto background = Sprite::create("FlappyResources/Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

	auto resumeButton = MenuItemImage::create( "FlappyResources/Resume_Normal.png", "FlappyResources/Resume_Clicked.png", CC_CALLBACK_1(PauseScene::resume, this) );
	auto retryButton = MenuItemImage::create( "FlappyResources/Retry_Normal.png", "FlappyResources/Retry_Clicked.png", CC_CALLBACK_1(PauseScene::retry, this) );
	auto quitButton = MenuItemImage::create( "FlappyResources/Quit_Normal.png", "FlappyResources/Quit_Clicked.png", CC_CALLBACK_1(PauseScene::goToMainMenuScene, this) );

	resumeButton->setPosition( origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2  + resumeButton->getContentSize().height * 2 );
	retryButton->setPosition( origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 );
	quitButton->setPosition( origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - resumeButton->getContentSize().height * 2 );

	auto menu = Menu::create( resumeButton, retryButton, quitButton, NULL );
	menu->setPosition( Vec2(0, 0) );

	this->addChild(menu);
	
	return true;
}


void PauseScene::goToMainMenuScene(Ref* sender)	{
	auto menuScene = MainMenuScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(menuScene);
}


void PauseScene::resume(Ref* sender)	{
	Director::getInstance()->popScene();
}


void PauseScene::retry(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->popScene();
	Director::getInstance()->replaceScene(TransitionFade::create(TRAINSITION_TIME, gameScene) );
}
