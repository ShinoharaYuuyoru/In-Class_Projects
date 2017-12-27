#pragma once;

#include <Common.h>
#include "MicroManager.h"

namespace F92
{
class MedicManager : public MicroManager
{
public:

	MedicManager();
	void executeMicro(const BWAPI::Unitset & targets);
};
}