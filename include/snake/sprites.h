#pragma once
#include "display/Display.h"

class DrawableInferface
{
public:
    virtual void render(DisplayInterface &) = 0;
};