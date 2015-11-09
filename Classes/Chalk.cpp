#include "Chalk.h"
#include "ConfigUtil.h"
#include "SampleListener.h"

USING_NS_CC;
Chalk* Chalk::create(ChalkState chalk_state)
{
	Chalk *pRet = new(std::nothrow) Chalk(chalk_state);
	CALL_INIT();
}

Chalk::Chalk(ChalkState chalk_state) :m_chalk_state_(chalk_state)
{
}

bool Chalk::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	//	this->setTag(kBlockTag);

	// Create Block
	//	mainSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(texture[random(0, 5)]));
	mainSprite = Sprite::createWithSpriteFrameName(CHALK);
//	if (m_chalk_state_ == ChalkState::ON_HAND)
//		this->setRotation(random(-30.0f, 30.0f));
	this->addChild(mainSprite);

	physics_body_->addShape(PhysicsShapeBox::create(mainSprite->getTextureRect().size, kStudentMaterial));
	physics_body_->setCategoryBitmask(0x0000000F);
	physics_body_->setCollisionBitmask(0x00000000);
	//		physics_body_->setCollisionBitmask(0xFF000000);
	physics_body_->setContactTestBitmask(0xFFFFFFFF);

	return true;
}

void Chalk::onEnter()
{
	BaseObject::onEnter();
}

void Chalk::onDestroy()
{
	BaseObject::onDestroy();
}

void Chalk::update(float delta_time)
{
	switch (m_chalk_state_)
	{
	case ChalkState::NA: break;
	case ChalkState::ON_HAND:
		//		this->setPosition(Vec2(SampleListener::getHandPosition().x, SampleListener::getHandPosition().y));
		break;
	case ChalkState::THROW: break;
	default: break;
	}
}

void Chalk::onContact(Message& message)
{
	CCLOG("%s", message.getString(CHALK_NAME));
	if (message.getString(CHALK_NAME) == CHALK_NAME)
		this->onDestroy();
}

void Chalk::initMessage()
{
	message_.putString(CHALK_NAME, CHALK_NAME);
}

void Chalk::setVelocity(cocos2d::Vec3 velocity)
{
	_physicsBody->setVelocity(Vec2(velocity.x, velocity.y));
}