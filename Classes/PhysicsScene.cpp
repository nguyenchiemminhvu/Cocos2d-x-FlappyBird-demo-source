#include "PhysicsScene.h"


PhysicsScene::PhysicsScene(void)
{
}


PhysicsScene::~PhysicsScene(void)
{
}


Scene* PhysicsScene::createScene()	{
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	scene->getPhysicsWorld()->setGravity(Vec2(0, -980));
	auto layer = PhysicsScene::create();
	layer->setPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);
	return scene;
}


bool PhysicsScene::init()	{
	if(!Layer::init())	{
		return false;
	}
	
	//draw frame
	auto frameBody = PhysicsBody::createEdgeBox(Size(Director::getInstance()->getVisibleSize()), PHYSICSBODY_MATERIAL_DEFAULT, 3);
	this->setPhysicsBody(frameBody);

	//Add a circle node to frame
	auto sprite = Sprite::create("CloseNormal.png");
	sprite->setPosition(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, 
						Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y);
	auto spriteBody = PhysicsBody::createBox(sprite->getContentSize());
	spriteBody->setCollisionBitmask(1);
	spriteBody->setContactTestBitmask(true);
	//spriteBody->applyForce(Vec2(-1000, 2000));
	//spriteBody->applyTorque(400);
	//spriteBody->applyImpulse(Vec2(500, 800));
	sprite->setPhysicsBody(spriteBody);
	this->addChild(sprite);

	/*
	//Add a circle node to frame
	auto sprite2 = Sprite::create("CloseNormal.png");
	sprite2->setPosition(Director::getInstance()->getVisibleSize().width / 2 + Director::getInstance()->getVisibleOrigin().x, 
						Director::getInstance()->getVisibleSize().height / 2 + Director::getInstance()->getVisibleOrigin().y - 100);
	auto spriteBody2 = PhysicsBody::createBox(sprite2->getContentSize());
	//spriteBody2->setDynamic(false);
	spriteBody2->setCollisionBitmask(2);
	spriteBody2->setContactTestBitmask(true);
	sprite2->setPhysicsBody(spriteBody2);
	this->addChild(sprite2);
	*/

	auto keyListener = EventListenerKeyboard::create();
	keyListener->onKeyPressed = [=] (EventKeyboard::KeyCode keyCode, Event* event)	{
		if(keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)	{
			sprite->getPhysicsBody()->setVelocity(Vec2(0, 300));
		}
	};

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(PhysicsScene::onContactBegin, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(PhysicsScene::onContactSeparate, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyListener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
	

	return true;
}


bool PhysicsScene::onContactBegin(PhysicsContact &contact)	{
	
	auto shapeA = contact.getShapeA()->getBody();
	auto shapeB = contact.getShapeB()->getBody();

	if(shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2 
		|| shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2)	{

			log("Collision has occured");
	}

	return true;
}


void PhysicsScene::onContactSeparate(PhysicsContact &contact)	{

	auto shapeA = contact.getShapeA();
	auto shapeB = contact.getShapeB();

	if(shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2 
		|| shapeA->getCollisionBitmask() == 1 && shapeB->getCollisionBitmask() == 2)	{

			log("Collision has separated");
	}
}