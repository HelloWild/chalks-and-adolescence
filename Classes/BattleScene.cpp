#include "BattleScene.h"
#include "ConfigUtil.h"
#include "Student.h"
#include "NewChalk.h"
#include "Edge.h"
#include "ControllerUtil.h"
#include "../proj.win32/main.h"

#include <atltrace.h>
#define TRACE ATLTRACE
#include "ChalkData.h"

USING_NS_CC;
using namespace std;

BattleScene* BattleScene::battleScene = nullptr;

BattleScene::BattleScene()
{
}

BattleScene::~BattleScene()
{
}

bool BattleScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// Init Physics World
	if (!this->initWithPhysics())
	{
		return false;
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, 0.0f));

	auto logo = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(BACKGROUNG_TEXTURE));
	logo->setPosition(config::visibleSize / 2);
	this->addChild(logo);

	Vec2 position_vector[] = { Vec2(1600.0f, 500.0f), Vec2(1000.0f, 540.0f),Vec2(400.0f,500.0f) ,
		Vec2(350.0f, 850.0f),Vec2(870.0f, 820.0f),Vec2(1600.0f, 850.0f) };

	// EDGE
	auto edge = Edge::create();
	edge->setPosition(config::visibleSize / 2);
	this->addChild(edge);


	StudentState stuState[] = { StudentState::STU1,StudentState::STU2, StudentState::STU3, StudentState::STU4, StudentState::STU5, StudentState::STU6 };
	for (int i = 0; i < 6; ++i)
	{
		auto student = Student::create(stuState[i]);
		student->setPosition(position_vector[i]);
		if (i < 3)
			this->addChild(student, 10);
		else
			this->addChild(student);
	}

	// Set Physics Debug Mode
//	this->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);


	// CHALK BOX
	auto chalkBox = Sprite::createWithSpriteFrameName(CHALK_BOX);
	chalkBox->setPosition(Vec2(960, 100));
	this->addChild(chalkBox, 20);
	//	chalkBox->

	auto chalkBox2 = Sprite::createWithSpriteFrameName(CHALK_BOX);
	chalkBox2->setPosition(Vec2(560, 100));
	this->addChild(chalkBox2, 20);

	auto chalkBox3 = Sprite::createWithSpriteFrameName(CHALK_BOX);
	chalkBox3->setPosition(Vec2(1360, 100));
	this->addChild(chalkBox3, 20);


	scheduleUpdate();

	// Game Controller Node
	auto controllerUtil = ControllerUtil::create();
	this->addChild(controllerUtil);

	new_chalk_ = NewChalk::create(NewChalkState::NA);
	this->addChild(new_chalk_,40);

	//	auto controller = Controller::create();
	//	this->addChild(controller, 0);
		// Mouse Layer
	//	auto mouseLayer = MouseLayer::create();
	//	this->addChild(mouseLayer, 4);

		// Keyboard Listener
	//	auto listenerKeyboard = EventListenerKeyboard::create();
	//	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(BattleScene::onKeyPressed, this);
	//	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);


	auto physicsListener = EventListenerPhysicsContact::create();
	physicsListener->onContactBegin = CC_CALLBACK_1(BattleScene::onContactBegin, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(physicsListener, this);

	return true;
}

BattleScene* BattleScene::getInstance()
{
	return battleScene;
}

void BattleScene::update(float delta_time)
{
	if (config::controlType == 0)
	{
		if (ControllerUtil::getMouseDown())
		{
			new_chalk_->setState(NewChalkState::ON_HAND);
		}
		else
		{
			if (new_chalk_->getState() == NewChalkState::ON_HAND)
			{
				auto chalk = NewChalk::create(NewChalkState::THROW);
				chalk->setPosition3D(Vec3(ControllerUtil::getMouseLocation().x, ControllerUtil::getMouseLocation().y, random(-140.0f, 140.0f)));
				chalk->setVelocity(Vec3(random(-1000.0f, 1000.0f), random(-1000.0f, 1000.0f), random(20.0f, -2000.0f)));
				this->addChild(chalk, 40);
			}
			new_chalk_->setState(NewChalkState::NA);
		}
	}
	else
	{
		if (playerHand->getStatus() == PlayerHand::HOLD)
		{
			new_chalk_->setState(NewChalkState::ON_HAND);
		}
		else if (playerHand->getStatus() == PlayerHand::EMPTY)
		{
			if (new_chalk_->getState() == NewChalkState::ON_HAND)
			{
				auto chalk = NewChalk::create(NewChalkState::THROW);
				MyPoint my_point = playerHand->getPosition();
				chalk->setPosition3D(Vec3(my_point.x, my_point.y, my_point.z));
				MyPoint velocity = playerHand->getSpeed();
				chalk->setVelocity(Vec3(velocity.x, velocity.y, velocity.z));
				this->addChild(chalk, 40);
			}
			new_chalk_->setState(NewChalkState::NA);
		}
	}

	//	if (config::controlType == 0)
	//	{
	//		if (ControllerUtil::getMoveDown())
	//		{
	//			Vec2 location = ControllerUtil::getMouseLocation();
	//			CCLOG("MOUSE %lf %lf", location.x, location.y);
	//			auto chalk = NewChalk::create(NewChalkState::ON_HAND);
	//			chalk->setPosition(ControllerUtil::getMouseLocation());
	//			this->addChild(chalk);
	//		}
	//	}
	//	else
	//	{
	//		switch (SampleListener::getHandState())
	//		{
	//		case HandState::EMPTY: break;
	//		case HandState::HOLD:
	//		{
	//			auto chalk = NewChalk::create(NewChalkState::ON_HAND);
	//			chalk->setPosition(Vec2(SampleListener::getHandPosition().x, SampleListener::getHandPosition().y));
	//			this->addChild(chalk);
	//			//		auto student = Student::create();
	//			//		student->setPosition(Vec2(SampleListener::getHandPosition().x, SampleListener::getHandPosition().y));
	//			//		this->addChild(student);
	//			break;
	//		}
	//		case HandState::THROW:
	//		{
	//			auto buf = new ChalkData();
	//			buf->s = SampleListener::getHandPosition();
	//			buf->v = SampleListener::getHandSpeed();
	//			EventCustom drop_event(DROP_EVENT);
	//			drop_event.setUserData(buf);
	//			_eventDispatcher->dispatchEvent(&drop_event);
	//			CC_SAFE_DELETE(buf);
	//			break;
	//		}
	//		default: break;
	//		}
	//	}

		//	CCLOG("BattleScene::update(float delta_time)");
	//	if (SampleListener::isInHand())
	//	{
	//		CCLOG("GET CHALK");
	//		if (chalk_on_hand == nullptr)
	//		{
	//			chalk_on_hand = Chalk::create(ChalkState::ON_HAND);
	//			//			chalk_on_hand->setPosition(Vec2(random(300.0f, 600.0f), random(300.0f, 600.0f)));
	//			chalk_on_hand->setPosition(Vec2(SampleListener::getHandPosition().x, SampleListener::getHandPosition().y));
	//			this->addChild(chalk_on_hand);
	//		}
	//	}
	//
	//	ChalkInThrowType chalk(MyPoint(0, 0, 0), MyPoint(0, 0, 0));
	//
	//	while (SampleListener::getChalkInThrow(chalk))
	//	{
	//		if (chalk_on_hand != nullptr)
	//		{
	//			chalk_on_hand->onDestroy();
	//			chalk_on_hand = nullptr;
	//		}
	//		auto chalk_sprite = Chalk::create(ChalkState::THROW);
	//		chalk_sprite->setPosition(Vec2(chalk.s.x, chalk.s.y));
	//		chalk_sprite->setVelocity(Vec3(chalk.v.x, chalk.v.y, chalk.v.z));
	//		this->addChild(chalk_sprite);
	//		CCLOG("THROW CHALK");
	//		CCLOG("%lf %lf %lf", chalk.s.x, chalk.s.y, chalk.s.z);
	//
	//	}


}

bool BattleScene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	auto nodeA = dynamic_cast<BaseObject*>(contact.getShapeA()->getBody()->getNode());
	auto nodeB = dynamic_cast<BaseObject*>(contact.getShapeB()->getBody()->getNode());
	if (nodeA != nullptr && nodeB != nullptr)
	{
		auto messageA = nodeA->getMessage();
		auto messageB = nodeB->getMessage();
		nodeA->onContact(messageB);
		nodeB->onContact(messageA);
	}
	return true;
}

void BattleScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
}