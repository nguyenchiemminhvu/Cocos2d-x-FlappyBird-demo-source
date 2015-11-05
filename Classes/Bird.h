#ifndef __BIRD_H__
#define __BIRD_H__

#pragma once
#include "cocos2d.h"
#include "Defination.h"

USING_NS_CC;

class Bird	{
public:
	Bird( Layer* layer );
	void flapping();

private:
	Sprite* bird;

	Size visibleSize;
	Vec2 origin;
};

#endif //__BIRD_H__