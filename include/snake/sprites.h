#pragma once
#include "display/Display.h"
#include "agipo/serial.h"

#define ANIM_DEBUG

class DrawableInferface
{
public:
    virtual void render(DisplayInterface &) = 0;
};

class Animation
{
	float lerp_time;
    bool _isEnded;
	float actual_time;
public:
	Animation(float lerp_time)
	: lerp_time(lerp_time), _isEnded(false), actual_time(0)
    {
#ifdef ANIM_DEBUG
		println("Triggered animation");
#endif
    }

	void Update(float delta_time) {
		actual_time += delta_time;
        if (isEnded())
            return;
		if (actual_time > lerp_time) {
            _isEnded = true;
#ifdef ANIM_DEBUG
			println("Animation End");
#endif
            OnEnd();
			return;
		}
		UpdateFunction(actual_time / lerp_time, delta_time);
	}

	virtual void UpdateFunction(float time, float delta_time) = 0;
	virtual void OnEnd() = 0;

    bool isEnded()
    {
        return _isEnded;
    }
};