//#include "MyController.h"
//
//Controller* MyController::controller = nullptr;
//SampleListener* MyController::listener = nullptr;
//
//void MyController::init()
//{
//	listener = new SampleListener();
//	controller = new Controller();
//	// Have the sample listener receive events from the controller
//	controller->addListener(*listener);
//}
//
//void MyController::destory()
//{
//	// Remove the sample listener when done
//	if (!listener&&!controller)
//		return;
//
//	controller->removeListener(*listener);
//
//	delete listener;
//	listener = nullptr;
//	delete controller;
//	controller = nullptr;
//}
//
//Controller* MyController::getController()
//{
//	return controller;
//}
