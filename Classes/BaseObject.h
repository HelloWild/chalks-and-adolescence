#pragma once

#include "cocos2d.h"
#include "Message.h"

#define CALL_INIT() \
if (pRet && pRet->init()) \
{ \
	pRet->autorelease(); \
	return pRet; \
} \
else \
{ \
	delete pRet; \
	pRet = NULL; \
	return NULL; \
}

class BaseObject : public cocos2d::Node
{
public:
	BaseObject();
	virtual ~BaseObject();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy();
	virtual void onContact(Message& message);
	virtual void initMessage();
	virtual Message getMessage();
//	virtual void setParent(Node* parent) override;
	void setVelocity(const cocos2d::Vect& velocity);
	float getVelocityMagnitude();
//	float getVelocityDirection();
protected:
	Message message_;
	float timer_;
	float hp_;
	float hp_max_;
	float velocity_magnitude_; // Velocity unit is pixel per second
	float velocity_direction_; // Velocity direction angle in radian measure
	cocos2d::PhysicsBody* physics_body_;
	cocos2d::Sprite* mainSprite;
	cocos2d::Vector<cocos2d::Sprite*> sprite_vector_;
};

