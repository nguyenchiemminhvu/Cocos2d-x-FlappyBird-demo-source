#include "Bird.h"


Bird::Bird( Layer* layer )	{
	visibleSize = Director::getInstance()->getVisibleSize();
	origin = Director::getInstance()->getVisibleOrigin();

	bird = Sprite::create( "FlappyResources/Ball.png" );
	bird->setPosition( Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2) );

	auto birdBody = PhysicsBody::createCircle( bird->getContentSize().width / 2 );
	birdBody->setCollisionBitmask( BIRD_COLLISION_BITMASK );
	birdBody->setContactTestBitmask( true );
	bird->setPhysicsBody( birdBody );

	layer->addChild( bird, 100 );
}


void Bird::flapping()	{
	this->bird->getPhysicsBody()->setVelocity( Vec2(0, 300) );
}