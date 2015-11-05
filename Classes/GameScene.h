#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#pragma once
#include "cocos2d.h"
#include "HUD.h"

USING_NS_CC;

class GameScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(GameScene);

	void goToPauseScene(Ref* sender);
	void goToGameOverScene(Ref* sender);

private:
	PhysicsWorld* physicsWorld;
	HUD* hud;

	void spawnPipe( float delta );

	void setPhysicsWorld(PhysicsWorld* world)	{ physicsWorld = world; }
	void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);
	void onKeyReleased(EventKeyboard::KeyCode keyCode, Event* event);

	bool onContactBegin(PhysicsContact& contact);
};

#endif //__GAME_SCENE_H__