/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
#include "PlayHand.h"

int main(int argc, char** argv) {
	PlayerHand playerHand;
	Controller controller;
	controller.addListener(playerHand);
	if (argc > 1 && strcmp(argv[1], "--bg") == 0)
		controller.setPolicy(Leap::Controller::POLICY_BACKGROUND_FRAMES);
	std::cin.get();

	while (1) {
		for (int i = 0; i < 0x1ffffff; ++i);
		switch (playerHand.getStatus())
		{
		case PlayerHand::ERROR:
			puts("无操作者");
			puts("手的位置和速度分别为:");
			playerHand.getPosition().out();
			playerHand.getSpeed().out();
			break;
		case PlayerHand::EMPTY:
			puts("手上为空");
			puts("手的位置和速度分别为:");
			playerHand.getPosition().out();
			playerHand.getSpeed().out();
			break;
		case PlayerHand::HOLD:
			puts("手握粉笔");
			puts("手的位置和速度分别为:");
			playerHand.getPosition().out();
			playerHand.getSpeed().out();
			break;
		default:
			break;
		}

	}


	controller.removeListener(playerHand);

	return 0;
}

