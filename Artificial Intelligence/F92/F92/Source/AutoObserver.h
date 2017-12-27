#pragma once

#include "Common.h"

namespace F92
{

class AutoObserver
{
    int                         _cameraLastMoved;
    int                         _unitFollowFrames;
    BWAPI::Unit      _observerFollowingUnit;

public:

    AutoObserver();
    void onFrame();
};

}