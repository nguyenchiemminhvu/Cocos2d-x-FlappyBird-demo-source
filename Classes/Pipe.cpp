#include "Pipe.h"
#include "Defination.h"

void Pipe::spawnPipe( Layer* layer )	{

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto origin = Director::getInstance()->getVisibleOrigin();
	auto ballSize = Sprite::create("FlappyResources/Ball.png")->getContentSize();
	auto random = CCRANDOM_0_1();
	if(random < LOWER_SCREEN_PIPE_THRESHOLD)	{
		random = LOWER_SCREEN_PIPE_THRESHOLD;
	}
	else if(random > UPPER_SCREEN_PIPE_THRESHOLD)	{
		random = UPPER_SCREEN_PIPE_THRESHOLD;
	}

	auto topPipe = Sprite::create("FlappyResources/Pipe.png");
	auto bottomPipe = Sprite::create("FlappyResources/Pipe.png");
	auto pointNode = Node::create();

	topPipe->setPosition( origin.x + visibleSize.width + topPipe->getContentSize().width / 2,
		(random * visibleSize.height) + (topPipe->getContentSize().height / 2) + (ballSize.height * PIPE_GAP) / 2 );
	bottomPipe->setPosition( topPipe->getPosition().x, 
		(random * visibleSize.height) - topPipe->getContentSize().height / 2 - (ballSize.height * PIPE_GAP) / 2 );
	pointNode->setPosition( origin.x + visibleSize.width + topPipe->getContentSize().width / 2,
		(random * visibleSize.height) );

	auto topPipeBody = PhysicsBody::createBox( topPipe->getContentSize() );
	topPipeBody->setDynamic( false );
	topPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
	topPipeBody->setContactTestBitmask( true );

	auto bottomPipeBody = PhysicsBody::createBox( bottomPipe->getContentSize() );
	bottomPipeBody->setDynamic( false );
	bottomPipeBody->setCollisionBitmask( OBSTACLE_COLLISION_BITMASK );
	bottomPipeBody->setContactTestBitmask( true );

	auto pointBody = PhysicsBody::createBox( Size(1, ballSize.height * PIPE_GAP) );
	pointBody->setDynamic( false );
	pointBody->setCollisionBitmask( POINT_COLLISION_BITMASK );
	pointBody->setContactTestBitmask( true );

	topPipe->setPhysicsBody( topPipeBody );
	bottomPipe->setPhysicsBody( bottomPipeBody );
	pointNode->setPhysicsBody( pointBody );

	layer->addChild( topPipe );
	layer->addChild( bottomPipe );
	layer->addChild( pointNode );

	auto moveTopPipe = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0) );
	auto moveBottomPipe = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize.width, Vec2(-visibleSize.width * 1.5, 0) );
	auto movePoint = MoveBy::create( PIPE_MOVEMENT_SPEED * visibleSize
		.width, Vec2(-visibleSize.width * 1.5, 0) );

	auto topSequence = Sequence::create( moveTopPipe, CallFunc::create(topPipe, callfunc_selector(Sprite::removeFromParent)), NULL );
	auto bottomSequence = Sequence::create( moveBottomPipe, CallFunc::create(bottomPipe, callfunc_selector(Sprite::removeFromParent)), NULL );
	auto pointSequence = Sequence::create( movePoint, CallFunc::create(pointNode, callfunc_selector(Node::removeFromParent)), NULL );

	topPipe->runAction( topSequence );
	bottomPipe->runAction( bottomSequence );
	pointNode->runAction( pointSequence );
}