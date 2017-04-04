#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Map.h"

namespace save
{
	void saveTheGame(game::GameInfo* gameInfo, game::MapCell** map);
}