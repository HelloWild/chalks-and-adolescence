#include "ControllerUtil.h"

USING_NS_CC;

bool ControllerUtil::move_up_ = false;
bool ControllerUtil::move_down_ = false;
bool ControllerUtil::move_left_ = false;
bool ControllerUtil::move_right_ = false;
bool ControllerUtil::mouse_down_ = false;
cocos2d::Vec2 ControllerUtil::mouse_location_ = Vec2();
bool ControllerUtil::key_e_pressed_ = false;
bool ControllerUtil::key_e_released_ = false;

ControllerUtil::~ControllerUtil()
{
	move_up_ = false;
	move_down_ = false;
	move_left_ = false;
	move_right_ = false;
	mouse_down_ = false;
	mouse_location_ = Vec2();
}

bool ControllerUtil::init()
{
	if (!Node::init())
	{
		return false;
	}

	// Keyboard Listener
	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(ControllerUtil::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(ControllerUtil::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);

	// Mouse Listener
	auto listenerMouse = EventListenerMouse::create();
	listenerMouse->onMouseDown = CC_CALLBACK_1(ControllerUtil::onMouseDown, this);
	listenerMouse->onMouseUp = CC_CALLBACK_1(ControllerUtil::onMouseUp, this);
	listenerMouse->onMouseMove = CC_CALLBACK_1(ControllerUtil::onMouseMove, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerMouse, this);

	return true;
}

bool ControllerUtil::getMoveUp()
{
	return move_up_;
}

bool ControllerUtil::getMoveDown()
{
	return move_down_;
}

bool ControllerUtil::getMoveLeft()
{
	return move_left_;
}

bool ControllerUtil::getMoveRight()
{
	return move_right_;
}

bool ControllerUtil::getMouseDown()
{
	return mouse_down_;
}

bool ControllerUtil::getKeyEPressed()
{
	if (key_e_pressed_ == true)
	{
		key_e_pressed_ = false;
		return true;
	}
	return false;
}

bool ControllerUtil::getKeyEReleased()
{
	if (key_e_released_ == true)
	{
		key_e_released_ = false;
		return true;
	}
	return false;
}

cocos2d::Vec2& ControllerUtil::getMouseLocation()
{
	return mouse_location_;
}

void ControllerUtil::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		move_up_ = true; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		move_down_ = true; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		move_left_ = true; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		move_right_ = true; break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		key_e_pressed_ = true; break;
	}
}

void ControllerUtil::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_W:
	case EventKeyboard::KeyCode::KEY_CAPITAL_W:
		move_up_ = false; break;
	case EventKeyboard::KeyCode::KEY_S:
	case EventKeyboard::KeyCode::KEY_CAPITAL_S:
		move_down_ = false; break;
	case EventKeyboard::KeyCode::KEY_A:
	case EventKeyboard::KeyCode::KEY_CAPITAL_A:
		move_left_ = false; break;
	case EventKeyboard::KeyCode::KEY_D:
	case EventKeyboard::KeyCode::KEY_CAPITAL_D:
		move_right_ = false; break;
	case EventKeyboard::KeyCode::KEY_E:
	case EventKeyboard::KeyCode::KEY_CAPITAL_E:
		key_e_released_ = false;
	default: break;
	}
}

void ControllerUtil::onMouseDown(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	mouse_down_ = true;
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}

void ControllerUtil::onMouseUp(cocos2d::Event* event)
{
	mouse_down_ = false;
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}

void ControllerUtil::onMouseMove(cocos2d::Event* event)
{
	auto e = static_cast<EventMouse*>(event);
	mouse_location_ = static_cast<EventMouse*>(event)->getLocationInView();
}
