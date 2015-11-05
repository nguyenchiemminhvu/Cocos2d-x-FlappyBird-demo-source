#ifndef __MAINMENU_SCENE_H__
#define __MAINMENU_SCENE_H__

#pragma once
#include "cocos2d.h"

USING_NS_CC;

class MainMenuScene : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();

	CREATE_FUNC(MainMenuScene);

private:
	void goToGameScene(Ref* sender);
};

#endif //__MAINMENU_SCENE_H__