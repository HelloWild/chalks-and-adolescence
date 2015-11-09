#include "NewChalk.h"
#include "ConfigUtil.h"
#include "SampleListener.h"
#include "ChalkData.h"
#include "ControllerUtil.h"
#include "../proj.win32/main.h"

USING_NS_CC;

NewChalk* NewChalk::create(NewChalkState chalk_state)
{
	NewChalk *pRet = new(std::nothrow) NewChalk(chalk_state);
	CALL_INIT();
}

NewChalk::NewChalk(NewChalkState chalk_state) :m_chalk_state_(chalk_state)
{

}

bool NewChalk::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	//	this->setTag(kBlockTag);

	// Create Block
	//	mainSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(texture[random(0, 5)]));
	mainSprite = Sprite::createWithSpriteFrameName(CHALK);
	this->addChild(mainSprite);
	this->setRotation(random(-40.0f, 40.0f));
	//
	physics_body_->addShape(PhysicsShapeBox::create(mainSprite->getTextureRect().size, kStudentMaterial));
	enterState(m_chalk_state_);
	//	//		physics_body_->setCollisionBitmask(0xFF000000);

//	auto self = this;
//	auto chalk_listener = EventListenerCustom::create(DROP_EVENT, [=](EventCustom* event)
//	{
//		auto buf = static_cast<ChalkData*>(event->getUserData());
////		std::cout << "EventListenerCustom" << std::endl;
//		CCLOG("EventListenerCustom v-x: %lf", buf->v.x);
//		self->position = buf->s;
//		self->velocity = buf->v;
//		self->m_chalk_state_ = NewChalkState::THROW;
////		switch (*buf)
////		self->onDestroy();
//	});
//	_eventDispatcher->addEventListenerWithSceneGraphPriority(chalk_listener, this);

	return true;
}

void NewChalk::onEnter()
{
	BaseObject::onEnter();
}

void NewChalk::onDestroy()
{
	CCLOG("THROW-Z:%f", this->getPositionZ());
	BaseObject::onDestroy();
}

void NewChalk::update(float delta_time)
{
	switch (m_chalk_state_)
	{
	case NewChalkState::NA:
		//		this->setOpacity(100.0f);
		break;
	case NewChalkState::ON_HAND:
		//		
		if (config::controlType == 0)
		{
			this->setPosition3D(Vec3(ControllerUtil::getMouseLocation().x, ControllerUtil::getMouseLocation().y, 0.0f));
			//			if (ControllerUtil::getMoveUp())
			//				m_chalk_state_ = NewChalkState::THROW;
		}
		else
		{
			MyPoint my_point = playerHand->getPosition();
			this->setPosition3D(Vec3(my_point.x, my_point.y, my_point.z));
		}
		break;
	case NewChalkState::THROW:
		//		this->setOpacity(0.0f);
		//		if (config::controlType == 0)
		//		{
		//			this->setPosition(ControllerUtil::getMouseLocation());
		//			physics_body_->setVelocity(Vec2(random(-40.0f, 40.0f), random(-40.0f, 40.0f)));
		//		}
		//		else
		//		{
		//			this->setPosition(Vec2(position.x, position.y));
		//			physics_body_->setVelocity(Vec2(velocity.x, velocity.y));
		//		}
		//		physics_body_->setContactTestBitmask(0xFFFFFFFF);
		//		physics_body_->setCollisionBitmask(0xFF000000);
		//		m_chalk_state_ = NewChalkState::NA;
		this->setPositionZ(this->getPositionZ() + delta_time*zVelocity*0.20);
		this->setRotation(this->getRotation() + delta_time*rotateVelocity);
		if (this->getPositionZ() > -280.0f && this->getPositionZ() < -40.0f)
		{
			physics_body_->setCategoryBitmask(0xFFFFFFFF);
			physics_body_->setContactTestBitmask(0xFFFFFFFF);
		}
		break;
	default: break;
	}

	this->setScale((350.0f + this->getPositionZ()) / 350.0f);

	if (this->getPositionZ() > 300.0f || this->getPositionZ() < -300.0f)
		this->onDestroy();
}

void NewChalk::enterState(NewChalkState state)
{
	m_chalk_state_ = state;
	switch (m_chalk_state_)
	{
	case NewChalkState::NA:
		this->setRotation(random(-40.0f, 40.0f));
		mainSprite->setOpacity(0.0f);
		physics_body_->setCategoryBitmask(0x0000000F);
		physics_body_->setCollisionBitmask(0x00000000);
		rotateVelocity = 0.0f;
		break;
	case NewChalkState::ON_HAND:
		mainSprite->setOpacity(1000.0f);
		physics_body_->setCategoryBitmask(0x0000000F);
		physics_body_->setCollisionBitmask(0x00000000);
		physics_body_->setContactTestBitmask(0x00000000);
		rotateVelocity = 0.0f;
		break;
	case NewChalkState::THROW:
		mainSprite->setOpacity(1000.0f);
		physics_body_->setCategoryBitmask(0xFFFF0000);
		physics_body_->setCollisionBitmask(0xFF000000);
		physics_body_->setContactTestBitmask(0xFFFF0000);
		rotateVelocity = random(-400.0f, 400.0f);
		break;
	default: break;
	}
}

void NewChalk::setState(NewChalkState state)
{
	if (m_chalk_state_ == state)
		return;
	exitState();
	enterState(state);
}

void NewChalk::exitState()
{
}

NewChalkState NewChalk::getState()
{
	return m_chalk_state_;
}

void NewChalk::onContact(Message& message)
{
	//	CCLOG("%s", message.getString(EDGE_NAME));
	if (message.getString(EDGE_NAME) == EDGE_NAME)
	{
		this->onDestroy();

//		auto particle = ParticleSystemQuad::create("particle/sleep_002.plist");
//		particle->setPosition(this->getPosition());
//		particle->setAutoRemoveOnFinish(true);
//		this->addChild(particle);

	} 
	else if(message.getString(STU_NAME) == STU_NAME)
	{
		this->onDestroy();
	}
}

void NewChalk::initMessage()
{
	message_.putString(CHALK_NAME, CHALK_NAME);
}

void NewChalk::setVelocity(cocos2d::Vec3 velocity)
{
	_physicsBody->setVelocity(Vec2(velocity.x, velocity.y));
	zVelocity = velocity.z;
}