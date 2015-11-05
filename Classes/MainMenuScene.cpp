#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* MainMenuScene::createScene()	{
	auto scene = Scene::create();
	auto layer = MainMenuScene::create();
	scene->addChild(layer);
	return scene;
}


bool MainMenuScene::init()	{
	if(!Layer::init())	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	
	//create background of main menu scene
	auto background = Sprite::create("FlappyResources/Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

	//create title
	auto title = Sprite::create("FlappyResources/Title.png");
	title->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height - title->getContentSize().height);
	this->addChild(title);

	//create Play item
	auto play = MenuItemImage::create("FlappyResources/Play_Button.png", "FlappyResources/Play_Button_Clicked.png", CC_CALLBACK_1(MainMenuScene::goToGameScene, this));
	play->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	
	auto menu = Menu::create(play, NULL);
	menu->setPosition(Vec2(0, 0));
	this->addChild(menu);


	return true;
}


void MainMenuScene::goToGameScene(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}