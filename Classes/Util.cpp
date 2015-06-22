#include "Util.h"

Util *instance = NULL;

Util::Util()
:m_callBack(nullptr)
{
}


Util::~Util()
{
}

Util* Util::getInstance()
{
	if (instance == NULL)
	{
		instance = new Util();
	}
	return instance;
}

void Util::performWithDelay(float time, CallBack callBack)
{
	m_callBack = callBack;
	CCDirector::sharedDirector()->getScheduler()->scheduleSelector(schedule_selector(Util::scheduleCallBack), this, time, 0, 0, false);
}

void Util::scheduleCallBack(float time)
{
	if (m_callBack)
	{
		m_callBack();
		m_callBack = nullptr;
	}
}