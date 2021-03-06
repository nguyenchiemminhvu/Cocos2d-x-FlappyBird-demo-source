#ifndef __SPLASH_SCENE_H__
#define __SPLASH_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class SplashScene : public Layer	{
public:
	static Scene* createScene();
	virtual bool init();
	
	CREATE_FUNC(SplashScene);

private:
	void goToMainMenuScene(float t);
};

#endif //__SPLASH_SCENE_H__