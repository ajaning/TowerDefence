#pragma once

#include "cocos2d.h"

USING_NS_CC;

typedef std::function<void(void)> CallBack;
// typedef void (*CallBack)(void);
//#define util_callback(_SELECTOR) (CallBack)(&_SELECTOR)

class Util : public CCObject
{
private:
	Util();
public:
	~Util();
	static Util* getInstance();
	void performWithDelay(float time, CallBack callBack);
	void scheduleCallBack(float time);

protected:
	CallBack m_callBack;
};

