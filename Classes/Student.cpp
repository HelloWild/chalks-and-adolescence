#include "Student.h"
#include "ConfigUtil.h"
#include "AudioEngine.h"

USING_NS_CC;
using namespace std;

StudentState stuState[] = { StudentState::STU1,StudentState::STU2, StudentState::STU3, StudentState::STU4, StudentState::STU5, StudentState::STU6 };
string texture[] = { STUDENT_1,STUDENT_2,STUDENT_3,STUDENT_4,STUDENT_5,STUDENT_6 };

Student* Student::create(StudentState student_state)
{
	Student *pRet = new(std::nothrow) Student(student_state);
	CALL_INIT();
}

Student::Student(StudentState student_state) :mStudentState(student_state), m_attack_state_(AttackState::NA)
{
}

bool Student::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	//	this->setTag(kBlockTag);

	// Create Block
//	mainSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(texture[random(0, 5)]));
	desk_sprite_ = Sprite::create();
	desk_sprite_->setPosition(0.0, -240.0f);
	this->addChild(desk_sprite_);

	mainSprite = Sprite::create();
	setState(mStudentState);
	this->addChild(mainSprite);
	

	enterState(mStudentState);

	this->setScale(0.9f);

	physics_body_->addShape(PhysicsShapeBox::create(mainSprite->getTextureRect().size, kStudentMaterial));
	//	physics_body_->setContactTestBitmask(kBlockContactMask);
	physics_body_->setCategoryBitmask(0x000000FF);
	physics_body_->setCollisionBitmask(0x0000FF00);
	physics_body_->setContactTestBitmask(0x0000FF00);

	initState();

	return true;
}

void Student::initState()
{
	this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
		if (random(0, 1))
		{
			m_student_doing_ = StudentDoing::WRONG;
		}
		else
		{
			m_student_doing_ = StudentDoing::GOOD;
		}
		enterState(mStudentState);
	}), DelayTime::create(15.0f), CallFuncN::create([&](Node* sender) {
		initState();
	}), nullptr));

	//	CallFuncN::create(CC_CALLBACK_1(Hero::stopBlinking, this));
}

void Student::onEnter()
{
	BaseObject::onEnter();
	auto background_music_ = experimental::AudioEngine::play2d("audio/BGM_Swingin_Chicks.mp3", true, 1.0f);
}

void Student::onDestroy()
{
	BaseObject::onDestroy();
}

void Student::update(float delta_time)
{
	updateStateMachine(delta_time);
}

void Student::onContact(Message& message)
{
	if (message.getString(CHALK_NAME) == CHALK_NAME)
	{
//		mainSprite->setOpacity(0.5f);
		m_attack_state_ = AttackState::ATTACK;
	}
}

void Student::initMessage()
{
	message_.putString(STU_NAME, STU_NAME);
}

void Student::updateStateMachine(float delta_time)
{
	if (m_student_doing_ == StudentDoing::WRONG && m_attack_state_ == AttackState::ATTACK)
	{
//		auto particle = ParticleSystemQuad::create("particle/sleep_001.plist");
//		particle->setPosition(this->getPosition());
//		particle->setAutoRemoveOnFinish(true);
//		this->addChild(particle);

		switch (mStudentState)
		{
		case StudentState::NA: break;
		case StudentState::STU1:
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student1-2.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student1-3.png");
			}), nullptr));
			break;
		case StudentState::STU2:
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student2-2.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student2-3.png");
			}), nullptr));
			break;
		case StudentState::STU3: 
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-6.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-7.png");
			}), nullptr));
			break;
		case StudentState::STU4:
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student4-2.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student4-3.png");
			}), nullptr));
			break;
		case StudentState::STU5:
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student5-2.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student5-3.png");
				auto hair = Sprite::createWithSpriteFrameName("texture/hair.png");
				hair->setPosition(140.0f, 250.0f);
				this->addChild(hair);
			}), nullptr));
			break;
		case StudentState::STU6: 
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student6-2.png");
			}), DelayTime::create(1.5f), CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student6-3.png");
				auto bird = Sprite::createWithSpriteFrameName("texture/student6-3bird.png");
				bird->setPosition(40.0f, 200.0f);
				this->addChild(bird);
			}), nullptr));
			break;
		default: break;
		}
		m_student_doing_ = StudentDoing::ELSE;
		m_attack_state_ = AttackState::NA;
	}
	
}

void Student::setState(StudentState student_state)
{
	if (mStudentState == student_state)
		return;
	exitState();
	enterState(student_state);
}

void Student::enterState(StudentState student_state)
{
	mStudentState = student_state;
	switch (mStudentState)
	{
	case StudentState::STU1:
		if (m_student_doing_ == StudentDoing::GOOD)
			mainSprite->setSpriteFrame(STUDENT_1);
		else
			mainSprite->setSpriteFrame("texture/student1-1.png");
		desk_sprite_->setSpriteFrame("texture/desk1.png");
		break;
	case StudentState::STU2:
		if (m_student_doing_ == StudentDoing::GOOD)
			mainSprite->setSpriteFrame(STUDENT_2);
		else
			mainSprite->setSpriteFrame("texture/student2-1.png");
		desk_sprite_->setSpriteFrame("texture/desk2.png");
		break;
	case StudentState::STU3:
		if (m_student_doing_ == StudentDoing::GOOD)
		{
			mainSprite->setSpriteFrame(STUDENT_3);
		}
		else
		{
			this->runAction(Sequence::create(CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-1.png");
			}), 
				DelayTime::create(1.0f), 
				CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-2.png");
			}), 
				DelayTime::create(1.0f),
				CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-3.png");
			}),
				DelayTime::create(1.0f),
				CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-4.png");
			}),
				DelayTime::create(1.0f),
				CallFuncN::create([&](Node* sender) {
				mainSprite->setSpriteFrame("texture/student3-5.png");
			}),
				nullptr));
		}
		desk_sprite_->setSpriteFrame("texture/desk3.png");
		break;
	case StudentState::STU4:
		if (m_student_doing_ == StudentDoing::GOOD)
		{
			mainSprite->setSpriteFrame(STUDENT_4);
		}
		else
		{
			mainSprite->setSpriteFrame("texture/student4-1.png");
			auto love = Sprite::createWithSpriteFrameName("texture/love.png");
			love->setPosition(140.0f, 200.0f);
			this->addChild(love);
		}
		desk_sprite_->setSpriteFrame("texture/desk4.png");
		break;
	case StudentState::STU5:
		if (m_student_doing_ == StudentDoing::GOOD)
		{
			mainSprite->setSpriteFrame(STUDENT_5);
		}
		else
		{
			mainSprite->setSpriteFrame("texture/student5-1.png");
			auto love = Sprite::createWithSpriteFrameName("texture/love.png");
			love->setPosition(-140.0f, 200.0f);
			this->addChild(love);
		}
		desk_sprite_->setSpriteFrame("texture/desk5.png");
		desk_sprite_->setPosition(40.0, -250.0f);
		break;
	case StudentState::STU6:
		if (m_student_doing_ == StudentDoing::GOOD)
		{
			mainSprite->setSpriteFrame(STUDENT_6);
		}
		else
		{
			mainSprite->setSpriteFrame("texture/student6-1.png");
			auto plane = Sprite::createWithSpriteFrameName("texture/plane.png");
			plane->setPosition(-200.0f, -60.0f);
			plane->setScale(0.6f);
			this->addChild(plane);
		}
		desk_sprite_->setSpriteFrame("texture/desk6.png");
		break;
	default:
		setState(stuState[random(0, 5)]);
		break;
	}
}

void Student::exitState()
{
}

void Student::addBird()
{
//	auto bird = Sprite::createWithSpriteFrameName("texture/student6-3bird.png");
//	bird->setPosition(40.0f, 100.0f);
//	this->addChild(bird);
//	this->runAction(Sequence::create(DelayTime::create(2.0f), CallFuncN::create([&](Node* sender) {
//		bird->removeFromParentAndCleanup(true);
//	}, nullptr));
}