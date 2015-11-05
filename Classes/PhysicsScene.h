#ifndef __PHYSICS_SCENE_H__
#define __PHYSICS_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class PhysicsScene : public Layer
{
public:
	PhysicsScene(void);
	virtual ~PhysicsScene(void);

	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(PhysicsScene);

private:
	PhysicsWorld* world;

	void setPhysicsWorld(PhysicsWorld* pWorld)	{ world = pWorld; }
	bool onContactBegin(PhysicsContact &contact);
	void onContactSeparate(PhysicsContact &contact);
};

#endif //__PHYSICS_SCENE_H__