#pragma once
#include "BaseObject.h"
class Edge : public BaseObject
{
public:
	static Edge* create();
	Edge();
	virtual bool init() override;
	virtual void onEnter() override;
	virtual void onDestroy() override;
	virtual void update(float delta_time) override;

	virtual void onContact(Message& message) override;
	virtual void initMessage() override; 
};

