#include "Edge.h"
#include "ConfigUtil.h"

USING_NS_CC;

Edge* Edge::create()
{
	Edge *pRet = new(std::nothrow) Edge();
	CALL_INIT();
}

Edge::Edge()
{
}

bool Edge::init()
{
	if (!BaseObject::init())
	{
		return false;
	}

	//	this->setTag(kBlockTag);

	// Create Block
	//	mainSprite = Sprite::createWithTexture(Director::getInstance()->getTextureCache()->getTextureForKey(texture[random(0, 5)]));
	mainSprite = Sprite::create();
//	mainSprite->setTextureRect(Rect(Vec2(0.0f, 0.0f), Size(1280.0f, 720.0f)));
	this->addChild(mainSprite);
	physics_body_->addShape(PhysicsShapeEdgeBox::create(config::visibleSize, kStudentMaterial, 10.0f));
	//	physics_body_->setContactTestBitmask(kBlockContactMask);
	physics_body_->setCategoryBitmask(0xFFFF0000);
	physics_body_->setContactTestBitmask(0xFFFF0000);

	return true;
}

void Edge::onEnter()
{
	BaseObject::onEnter();
}

void Edge::onDestroy()
{
	BaseObject::onDestroy();
}

void Edge::update(float delta_time)
{
}

void Edge::onContact(Message& message)
{
}

void Edge::initMessage()
{
	message_.putString(EDGE_NAME, EDGE_NAME);
}