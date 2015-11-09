#include "SampleListener.h"
#include "cocos2d.h"

cocos2d::Vec3 SampleListener::Myfinger[3];
cocos2d::Vec3 SampleListener::handPosition;
cocos2d::Vec3 SampleListener::handSpeed;
HandState SampleListener::handState = HandState::EMPTY;

void SampleListener::onInit(const Controller& controller) {
//	std::cout << "Initialized" << std::endl;
//	CCLOG("Initialized");
}

void SampleListener::onConnect(const Controller& controller) {
//	std::cout << "Connected" << std::endl;
//	CCLOG("Connected");
	controller.enableGesture(Gesture::TYPE_CIRCLE);
	controller.enableGesture(Gesture::TYPE_KEY_TAP);
	controller.enableGesture(Gesture::TYPE_SCREEN_TAP);
	controller.enableGesture(Gesture::TYPE_SWIPE);
}

void SampleListener::onDisconnect(const Controller& controller) {
	// Note: not dispatched when running in a debugger.
//	std::cout << "Disconnected" << std::endl;
//	CCLOG("Disconnected");
}

void SampleListener::onExit(const Controller& controller) {
//	std::cout << "Exited" << std::endl;
//	CCLOG("Exited");
}

void SampleListener::onFrame(const Controller& controller) {
	// Get the most recent frame and report some basic information
	const Frame frame = controller.frame();
//	CCLOG("Frame id: %d", frame.id());
//	CCLOG("timestamp: %d", frame.timestamp());
//	CCLOG("hands: %d", frame.hands().count());
	HandList hands = frame.hands();
	if (hands.begin() == hands.end()) {
		for (int i = 0; i < 3; ++i)
			Myfinger[i] = cocos2d::Vec3(1e5, 1e5, 1e5);
		handPosition = cocos2d::Vec3(1e5, 1e5, 1e5);
		//handSpeed = Point(0, 0, 0);
	}

	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
		// Get the first hand
		const Hand hand = *hl;
		handPosition = cocos2d::Vec3(hand.palmPosition().x + 960, hand.palmPosition().y * 2.8, hand.palmPosition().z);
		handSpeed = cocos2d::Vec3(hand.palmVelocity().x, hand.palmVelocity().y, hand.palmVelocity().z);

		const Vector normal = hand.palmNormal();
		const Vector direction = hand.direction();

		// Calculate the hand's pitch, roll, and yaw angles
		// Get the Arm bone
		Arm arm = hand.arm();
		// Get fingers
		const FingerList fingers = hand.fingers();

		int tot = -1;
		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
			const Finger finger = *fl;
			tot++;
			if (tot == 3) break;
			// Get finger bones
			//  std::cout << std::endl;
			for (int b = 3; b < 4; ++b) {
				Bone::Type boneType = static_cast<Bone::Type>(b);
				Bone bone = finger.bone(boneType);
				//	std::cout << bone.basis().xBasis << std::endl;
				//	std::cout << bone.basis().yBasis << std::endl;
				//	std::cout << bone.basis().zBasis << std::endl;
				Myfinger[tot].x = bone.nextJoint().x;
				Myfinger[tot].y = bone.nextJoint().y;
				Myfinger[tot].z = bone.nextJoint().z;
			}
			//	break;
		}
	}

	// Get tools
	const ToolList tools = frame.tools();
	for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
		const Tool tool = *tl;
	}

	// Get gestures
	const GestureList gestures = frame.gestures();
	for (int g = 0; g < gestures.count(); ++g) {
		Gesture gesture = gestures[g];

		switch (gesture.type()) {

		case Gesture::TYPE_CIRCLE:
		{
			CircleGesture circle = gesture;
			std::string clockwiseness;

			if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
				clockwiseness = "clockwise";
			}
			else {
				clockwiseness = "counterclockwise";
			}

			// Calculate angle swept since last frame
			float sweptAngle = 0;
			if (circle.state() != Gesture::STATE_START) {
				CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
				sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
			}
			break;
		}
		case Gesture::TYPE_SWIPE:
		{
			SwipeGesture swipe = gesture;
			break;
		}
		case Gesture::TYPE_KEY_TAP:
		{
			KeyTapGesture tap = gesture;
			break;
		}
		case Gesture::TYPE_SCREEN_TAP:
		{
			ScreenTapGesture screentap = gesture;
			break;
		}
		default:
			break;
		}
	}

	if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
		// std::cout << std::endl;
	}



//	std::cout << "Frame id: " << frame.id()
//		<< ", timestamp: " << frame.timestamp()
//		<< ", hands: " << frame.hands().count()
//		<< ", extended fingers: " << frame.fingers().extended().count()
//		<< ", tools: " << frame.tools().count()
//		<< ", gestures: " << frame.gestures().count() << std::endl;
//
//	HandList hands = frame.hands();
//	for (HandList::const_iterator hl = hands.begin(); hl != hands.end(); ++hl) {
//		// Get the first hand
//		const Hand hand = *hl;
//		std::string handType = hand.isLeft() ? "Left hand" : "Right hand";
//		std::cout << std::string(2, ' ') << handType << ", id: " << hand.id()
//			<< ", palm position: " << hand.palmPosition() << std::endl;
//		// Get the hand's normal vector and direction
//		const Vector normal = hand.palmNormal();
//		const Vector direction = hand.direction();
//
//		// Calculate the hand's pitch, roll, and yaw angles
//		std::cout << std::string(2, ' ') << "pitch: " << direction.pitch() * RAD_TO_DEG << " degrees, "
//			<< "roll: " << normal.roll() * RAD_TO_DEG << " degrees, "
//			<< "yaw: " << direction.yaw() * RAD_TO_DEG << " degrees" << std::endl;
//
//		// Get the Arm bone
//		Arm arm = hand.arm();
//		std::cout << std::string(2, ' ') << "Arm direction: " << arm.direction()
//			<< " wrist position: " << arm.wristPosition()
//			<< " elbow position: " << arm.elbowPosition() << std::endl;
//
//		// Get fingers
//		const FingerList fingers = hand.fingers();
//		for (FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); ++fl) {
//			const Finger finger = *fl;
//			std::cout << std::string(4, ' ') << fingerNames[finger.type()]
//				<< " finger, id: " << finger.id()
//				<< ", length: " << finger.length()
//				<< "mm, width: " << finger.width() << std::endl;
//
//			// Get finger bones
//			for (int b = 0; b < 4; ++b) {
//				Bone::Type boneType = static_cast<Bone::Type>(b);
//				Bone bone = finger.bone(boneType);
//				std::cout << std::string(6, ' ') << boneNames[boneType]
//					<< " bone, start: " << bone.prevJoint()
//					<< ", end: " << bone.nextJoint()
//					<< ", direction: " << bone.direction() << std::endl;
//			}
//		}
//	}
//
//	// Get tools
//	const ToolList tools = frame.tools();
//	for (ToolList::const_iterator tl = tools.begin(); tl != tools.end(); ++tl) {
//		const Tool tool = *tl;
//		std::cout << std::string(2, ' ') << "Tool, id: " << tool.id()
//			<< ", position: " << tool.tipPosition()
//			<< ", direction: " << tool.direction() << std::endl;
//	}
//
//	// Get gestures
//	const GestureList gestures = frame.gestures();
//	for (int g = 0; g < gestures.count(); ++g) {
//		Gesture gesture = gestures[g];
//
//		switch (gesture.type()) {
//		case Gesture::TYPE_CIRCLE:
//		{
//			CircleGesture circle = gesture;
//			std::string clockwiseness;
//
//			if (circle.pointable().direction().angleTo(circle.normal()) <= PI / 2) {
//				clockwiseness = "clockwise";
//			}
//			else {
//				clockwiseness = "counterclockwise";
//			}
//
//			// Calculate angle swept since last frame
//			float sweptAngle = 0;
//			if (circle.state() != Gesture::STATE_START) {
//				CircleGesture previousUpdate = CircleGesture(controller.frame(1).gesture(circle.id()));
//				sweptAngle = (circle.progress() - previousUpdate.progress()) * 2 * PI;
//			}
//			std::cout << std::string(2, ' ')
//				<< "Circle id: " << gesture.id()
//				<< ", state: " << stateNames[gesture.state()]
//				<< ", progress: " << circle.progress()
//				<< ", radius: " << circle.radius()
//				<< ", angle " << sweptAngle * RAD_TO_DEG
//				<< ", " << clockwiseness << std::endl;
//			break;
//		}
//		case Gesture::TYPE_SWIPE:
//		{
//			SwipeGesture swipe = gesture;
//			std::cout << std::string(2, ' ')
//				<< "Swipe id: " << gesture.id()
//				<< ", state: " << stateNames[gesture.state()]
//				<< ", direction: " << swipe.direction()
//				<< ", speed: " << swipe.speed() << std::endl;
//			break;
//		}
//		case Gesture::TYPE_KEY_TAP:
//		{
//			KeyTapGesture tap = gesture;
//			std::cout << std::string(2, ' ')
//				<< "Key Tap id: " << gesture.id()
//				<< ", state: " << stateNames[gesture.state()]
//				<< ", position: " << tap.position()
//				<< ", direction: " << tap.direction() << std::endl;
//			break;
//		}
//		case Gesture::TYPE_SCREEN_TAP:
//		{
//			ScreenTapGesture screentap = gesture;
//			std::cout << std::string(2, ' ')
//				<< "Screen Tap id: " << gesture.id()
//				<< ", state: " << stateNames[gesture.state()]
//				<< ", position: " << screentap.position()
//				<< ", direction: " << screentap.direction() << std::endl;
//			break;
//		}
//		default:
//			std::cout << std::string(2, ' ') << "Unknown gesture type." << std::endl;
//			break;
//		}
//	}
//
//	if (!frame.hands().isEmpty() || !gestures.isEmpty()) {
//		std::cout << std::endl;
//	}
}

void SampleListener::onFocusGained(const Controller& controller) {
//	std::cout << "Focus Gained" << std::endl;
	CCLOG("Focus Gained");
}

void SampleListener::onFocusLost(const Controller& controller) {
//	std::cout << "Focus Lost" << std::endl;
	CCLOG("Focus Lost");
}

void SampleListener::onDeviceChange(const Controller& controller) {
//	std::cout << "Device Changed" << std::endl;
	CCLOG("Device Changed");
//	const DeviceList devices = controller.devices();
//
//	for (int i = 0; i < devices.count(); ++i) {
//		std::cout << "id: " << devices[i].toString() << std::endl;
//		std::cout << "  isStreaming: " << (devices[i].isStreaming() ? "true" : "false") << std::endl;
//	}
}

void SampleListener::onServiceConnect(const Controller& controller) {
//	std::cout << "Service Connected" << std::endl;
	CCLOG("Service Connected");
}

void SampleListener::onServiceDisconnect(const Controller& controller) {
//	std::cout << "Service Disconnected" << std::endl;
	CCLOG("Service Disconnected");
}

int SampleListener::scraft()
{
	double t1 = Myfinger[0].distance(Myfinger[1]);
	CCLOG("F1 %lf", t1);
	double t2 = Myfinger[0].distance(Myfinger[2]);
	double t3 = Myfinger[1].distance(Myfinger[2]);
	CCLOG("F1 %lf", t2);
	CCLOG("F1 %lf", t3);
	return (t1 < 20 || t2 < 20 || t3 < 20);
}

cocos2d::Vec3 SampleListener::getHandPosition()
{
	return handPosition;
}

cocos2d::Vec3 SampleListener::getHandSpeed()
{
	return handSpeed;
}

HandState SampleListener::getHandState()
{
	switch(handState)
	{
	case HandState::EMPTY:
		if (scraft()) {
			if (handPosition.distance(cocos2d::Vec3(960, 300, 0)) < 150000)
			{
				CCLOG("### HOLD CHALK ###");
				handState = HandState::WAIT_THROW;
				return HandState::HOLD;
			}
		}
		break;
	case HandState::WAIT_THROW: 
		if(!scraft())
		{
			if (handSpeed.distance(cocos2d::Vec3(0, 0, 0)) * 3 > 50)
			{
				CCLOG("### THROW CHALK ###");
				handState = HandState::EMPTY;
				return HandState::THROW;
			}
		}
		break;
	default: break;
	}
	return handState;
}