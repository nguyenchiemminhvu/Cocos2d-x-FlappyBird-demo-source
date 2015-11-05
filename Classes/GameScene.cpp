#include "GameScene.h"
#include "PauseScene.h"
#include "GameOverScene.h"
#include "Defination.h"
#include "Pipe.h"
#include "Bird.h"
#include "SimpleAudioEngine.h"


Scene* GameScene::createScene()	{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity( Vec2(0, -980) );

	auto layer = GameScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	
	scene->addChild(layer);
	return scene;
}


bool GameScene::init()	{
	if(!Layer::init())	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();

	//create frame physics body
	auto frameBody = PhysicsBody::createEdgeBox( Size(visibleSize), PHYSICSBODY_MATERIAL_DEFAULT, 3 );
	frameBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
	frameBody->setContactTestBitmask( true );
	this->setPhysicsBody( frameBody );

	//create a flappy bird
	auto bird = new Bird( this );

	//key event listener
	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = CC_CALLBACK_2( GameScene::onKeyPressed, this );
	keyListener->onKeyReleased = CC_CALLBACK_2( GameScene::onKeyReleased, this );

	//contact event listener
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1( GameScene::onContactBegin, this );

	//touch event listener
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->setSwallowTouches( true );
	touchListener->onTouchBegan = [=] (Touch* touch, Event* event) -> bool	{
		bird->flapping();
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( "Sounds/Wing.mp3" );
		return true;
	};

	//add event listener to dispatcher
	_eventDispatcher->addEventListenerWithSceneGraphPriority( keyListener, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( contactListener, this );
	_eventDispatcher->addEventListenerWithSceneGraphPriority( touchListener, this );

	//schedule timer on spawn Pipe
	this->schedule( schedule_selector(GameScene::spawnPipe), PIPE_SPAWN_FREQUENCY * visibleSize.width );

	hud = HUD::createHUD();
	this->addChild( hud, 500 );

	return true;
}


void GameScene::spawnPipe( float delta )	{
	Pipe::spawnPipe( this );
}


void GameScene::goToPauseScene(Ref* sender)	{
	auto pauseScene = PauseScene::createScene();
	Director::getInstance()->pushScene(pauseScene);
}


void GameScene::goToGameOverScene(Ref* sender)	{
	auto gameOverScene = GameOverScene::createScene( hud->getScore() );
	Director::getInstance()->replaceScene( gameOverScene );
}


void GameScene::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)	{
	
}


void GameScene::onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)	{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_P: 
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->goToPauseScene(this);
		break;
	default:
		break;
	}
}


bool GameScene::onContactBegin(PhysicsContact& contact)	{
	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	auto bitmaskA = shapeA->getCollisionBitmask();
	auto bitmaskB = shapeB->getCollisionBitmask();

	if( (bitmaskA == BIRD_COLLISION_BITMASK && bitmaskB == OBSTACLE_COLLISION_BITMASK)
		|| (bitmaskA == OBSTACLE_COLLISION_BITMASK && bitmaskB == BIRD_COLLISION_BITMASK) )	   {
		
		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( "Sounds/Hit.mp3" );
		goToGameOverScene( this );
	}

	if( (bitmaskA == BIRD_COLLISION_BITMASK && bitmaskB == POINT_COLLISION_BITMASK)
		|| (bitmaskA == POINT_COLLISION_BITMASK && bitmaskB == BIRD_COLLISION_BITMASK) )	{

		CocosDenshion::SimpleAudioEngine::getInstance()->playEffect( "Sounds/Point.mp3" );
		hud->increaseScore();
	}
	return true;
}
