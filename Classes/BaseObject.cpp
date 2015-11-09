#include "BaseObject.h"
#include "ConfigUtil.h"

USING_NS_CC;

BaseObject::BaseObject()
{
}

BaseObject::~BaseObject()
{
}

bool BaseObject::init()
{
	if (!Node::init())
	{
		return false;
	}
	// Initial Message
	initMessage();

	// Create Physics Body
	physics_body_ = PhysicsBody::create();
	physics_body_->setRotationEnable(false);
	this->setPhysicsBody(physics_body_);

	this->scheduleUpdate();

	return true;
}

void BaseObject::onEnter()
{
	Node::onEnter();
}

void BaseObject::onDestroy()
{
	this->removeFromParentAndCleanup(true);
}

void BaseObject::onContact(Message& message)
{
}

void BaseObject::initMessage()
{
}

Message BaseObject::getMessage()
{
	return message_;
}

void BaseObject::setVelocity(const cocos2d::Vect& velocity)
{
	if (physics_body_)
		physics_body_->setVelocity(velocity);
}

float BaseObject::getVelocityMagnitude()
{
	return physics_body_->getVelocity().length();
}

//float BaseObject::getVelocityDirection()
//{
//}