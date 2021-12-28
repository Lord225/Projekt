#pragma once
#include "sprites.h"
#include "point.h"
#include "pad.h"
#include <deque>
#include <algorithm>

class Snake : public DrawableInferface
{
    Point head;
    std::deque<Point> tail;
    size_t max = 5;
public:
    enum CollisionClass
    {
        None = 0,
        Wall = 1,
        Self = 2,
    };

    std::pair<int,int> dir_to_vec(PAD::DIR dir)
    {
        switch (dir)
        {
        case PAD::DIR::UP:
            return {1, 0};
        case PAD::DIR::DOWN:
            return {-1, 0};
        case PAD::DIR::RIGHT:
            return {0, 1};
        case PAD::DIR::LEFT:
            return {0, -1};
        case PAD::DIR::NONE:
        default:
            return {0, 0};
        
        }       
    }
    
    void reset(int posx, int posy, int size = 5)
    {
        tail.clear();
        head = {posx, posy};
        max = size;
    }

    CollisionClass check_for_colisions(Point& new_head)
    {
        if(new_head.x < 0 || new_head.x > 7)
            return CollisionClass::Wall;
        if(new_head.y < 0 || new_head.y > 7)
            return CollisionClass::Wall;
        
        for(auto& segment : tail)
            if(segment==new_head)
                return CollisionClass::Self;
        return CollisionClass::None;  
    }

    CollisionClass update(PAD::DIR DIR)
    {
        while(tail.size() > max)
            tail.pop_back();
        
        Point new_pos = head;
        new_pos += dir_to_vec(DIR);
        
        if(auto collision = check_for_colisions(new_pos); collision!=CollisionClass::None)
            return collision;

        tail.push_front(head);
        head = new_pos;

        return CollisionClass::None;
    }

    void render(DisplayInterface &render_on)
    {
        head.render(render_on);
        for(auto& segment : tail)
            segment.render(render_on);
    }
};