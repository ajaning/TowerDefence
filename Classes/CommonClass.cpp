//
//  CommonClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-9-27.
//
//

#include "CommonClass.h"
#include "LcdAdapClass.h"
static CommonClass* sharedCommon = NULL;

CommonClass::CommonClass()
{

}

CommonClass::~CommonClass()
{

}

bool CommonClass::init()
{

    
    return true;
}

CommonClass* CommonClass::getSharedCommon()
{
    if (sharedCommon == NULL) {
        sharedCommon = new CommonClass();
        sharedCommon->init();
    }
    return sharedCommon;
}



float CommonClass::ConvertSpeedToTime(float length, float speed)
{
    if (speed == 0) {
        return 0;
    }
    return (length / speed);
}

CCPoint CommonClass::getGameFromToRealPos(CCPoint fromPos,CCPoint toPos)
{
    
    
	CCSize size = LcdAdapClass::sharedLCDADAP()->getWinSize();
    
	CCPoint diffPos = ccpSub(toPos, fromPos);
	float realX = 0;
	float realY = 0;
	float delValue = 50;
    
    
	if((diffPos.x == 0) || (diffPos.y == 0))
	{
		if ((diffPos.x == 0) && (diffPos.y == 0)) {
			return fromPos;
		}
		else if (diffPos.x == 0)
		{
			if (diffPos.y < 0) {
				realY = -delValue;
			}
			else
			{
				realY = size.height + delValue;
			}
            
			realX = fromPos.x;
		}
		else if (diffPos.y == 0)
		{
			if (diffPos.x < 0) {
				realX = -delValue;
			}
			else
			{
				realX = size.width + delValue;
			}
			realY = fromPos.y;
		}
	}
	else
	{
        //		if (diffPos.x > 0) {
        //			realX = size.width + delValue;
        //		}
        //		else
        //		{
        //			realX = -delValue;
        //		}
        //
        //		float ratio = diffPos.y / diffPos.x;
        //
        //		realY = (realX - fromPos.x) * ratio + fromPos.y;
        //        if (realY >= size.height) {
        //            realY = size.height + delValue;
        //        }
        //        else if (realY <= 0)
        //        {
        //            realY = -delValue;
        //        }
		float ratio = diffPos.y / diffPos.x;
		if (diffPos.y > 0) {
			realY = size.height + delValue;
		}
		else
		{
			realY = -delValue;
		}
        realX = (realY - fromPos.y) / ratio + fromPos.x;
        if (realX > (size.width + delValue)) {
            realX = size.width + delValue;
            realY = realY = (realX - fromPos.x) * ratio + fromPos.y;
        }
        else if (realX < (-delValue))
        {
            realX = -delValue;
            realY = realY = (realX - fromPos.x) * ratio + fromPos.y;
        }
	}
    
	return CCPoint(realX,realY);
}