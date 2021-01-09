#include <iostream>

#include "utilities.hpp"
#include "parameter.hpp"

namespace Game
{
    Parameter::Parameter(float min, float max, float probChgMin, float probChgMax)
    {
        this->min = min;
        this->max = max;
        center = (max - min) / 2;
        this->probChgMin = probChgMin;
        this->probChgMax = probChgMax;
        adjust();
    }

    void Parameter::adjust()
    {
        float n = drand48();
        if (n > probChgMin && n < probChgMax)
        {
            _value = int(lerp(min, max, drand48()));
            chgCnt = 1 + int(drand48() * 10);
            cnt = 0;
        }
        // std::cout << _value << "," << chgCnt << std::endl;
    }

    float Parameter::update()
    {
        if (cnt >= chgCnt)
        {
            _value = 0;
            cnt = 0;
        }
        cnt++;

        return _value;
    }

    float Parameter::value()
    {
        return _value;
    }

    int Parameter::iValue()
    {
        return int(_value);
    }

} // namespace Game

