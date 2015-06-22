//
//  FontShowClass.cpp
//  CaratonFatans
//
//  Created by jack on 13-7-21.
//
//

#include "FontShowClass.h"

static FontShowClass* myFont = NULL;

FontShowClass::FontShowClass()
{

}

FontShowClass::~FontShowClass()
{
    
}

bool FontShowClass::init()
{

    return true;
}

FontShowClass* FontShowClass::sharedFont()
{
    if (myFont == NULL) {
        myFont = FontShowClass::create();
    }
    
    return myFont;
}