#pragma once

#include "cocos2d.h"

#define MAIN_TEXTURE_PLIST "texture/main_texture.plist"
#define MAIN_TEXTURE_PNG "texture/main_texture.png"

#define LOAD_SCENE_BACKGROUND "texture/load-scene.png"
#define BACKGROUNG_TEXTURE "texture/background.png"
#define STUDENT_1 "texture/student1.png"
#define STUDENT_2 "texture/student2.png"
#define STUDENT_3 "texture/student3.png"
#define STUDENT_4 "texture/student4.png"
#define STUDENT_5 "texture/student5.png"
#define STUDENT_6 "texture/student6.png"
#define CHALK_BOX "texture/chalk-box.png"
#define CHALK "texture/chalk.png"

#define EDGE_NAME "edge"
#define CHALK_NAME "chalk"
#define STU_NAME "student"

#define DROP_EVENT "DROP_EVENT"

#define kStudentMaterial cocos2d::PhysicsMaterial(10.0f, 1.0f, 0.0f)

namespace config
{
	// Variable
	extern cocos2d::Size visibleSize;
	extern cocos2d::Vec2 visibleOrigin;
	extern float visibleWidth;
	extern float visibleHeight;
	extern int controlType;
	// 0 mouse 1 leap motion
}

class ConfigUtil
{
};

