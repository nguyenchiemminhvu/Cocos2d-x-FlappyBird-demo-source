#include "GameOverScene.h"
#include "MainMenuScene.h"
#include "GameScene.h"
#include "Defination.h"


Scene* GameOverScene::createScene(uint64_t tempScore)	{
	score = tempScore;
	auto scene = Scene::create();
	auto layer = GameOverScene::create();
	scene->addChild(layer);
	return scene;
}


bool GameOverScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	UserDefault* userScore = UserDefault::getInstance();
	if(score >= userScore->getIntegerForKey( "highscore" ))	{
		userScore->setIntegerForKey( "highscore", score );
	}
	userScore->flush();

	//create background for game over scene
	auto background = Sprite::create("FlappyResources/Background.png");
	background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	this->addChild(background);

	//create retry item
	auto retry = MenuItemImage::create( "FlappyResources/Retry_Button.png", "FlappyResources/Retry_Button_Clicked.png", CC_CALLBACK_1(GameOverScene::goToGameScene, this) );
	retry->setPosition( origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 );

	//create quit item
	auto quit = MenuItemImage::create( "FlappyResources/Menu_Button.png", "FlappyResources/Menu_Button_Clicked.png", CC_CALLBACK_1(GameOverScene::goToMainMenuScene, this) );
	quit->setPosition( origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2 - quit->getContentSize().height * 2);

	//create menu
	auto menu = Menu::create( retry, quit, NULL );
	menu->setPosition( Vec2(0, 0) );

	//create label score
	auto stringScore = __String::createWithFormat( "Your score: %d", score );
	auto labelScore = LabelTTF::create( stringScore->getCString(), "fonts/Marker Belt.ttf", 50 );
	labelScore->setPosition( origin.x + labelScore->getContentSize().width, origin.y + visibleSize.height / 2 + labelScore->getContentSize().height * 4 );
	labelScore->setFontFillColor( Color3B::YELLOW );

	//create label display best score
	auto stringBestScore = __String::createWithFormat( "High score: %d", userScore->getIntegerForKey( "highscore" ) );
	auto labelHighScore = LabelTTF::create( stringBestScore->getCString(), "fonts/Marker Belt.ttf", 50 );
	labelHighScore->setPosition( origin.x + labelScore->getContentSize().width + visibleSize.width / 2, origin.y + visibleSize.height / 2 + labelHighScore->getContentSize().height * 4);
	labelHighScore->setFontFillColor( Color3B::RED );

	this->addChild( menu );
	this->addChild( labelScore );
	this->addChild( labelHighScore );

	return true;
}


void GameOverScene::goToMainMenuScene(Ref* sender)	{
	auto menuScene = MainMenuScene::createScene();
	Director::getInstance()->replaceScene( TransitionFade::create(TRAINSITION_TIME, menuScene) );
}


void GameOverScene::goToGameScene(Ref* sender)	{
	auto gameScene = GameScene::createScene();
	Director::getInstance()->replaceScene(gameScene);
}