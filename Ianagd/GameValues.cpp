#include "GameValues.h"


std::vector<gv::WaveValues> gv::wavesValues{
	gv::WaveValues{ 5, 80, 0.2f, 50, {100, 0, 0} },
	gv::WaveValues{ 8, 100, 0.3f, 50, {128, 80, 80} },
	gv::WaveValues{ 2, 800, 0.2f, 250, {255, 0, 0} },
	gv::WaveValues{ 10, 600, 0.3f, 200, {0, 0, 0}},
	gv::WaveValues{ 10, 1500, 0.3f, 200, {0, 0, 0}}
};

std::vector<gv::TowerValues> gv::towersValues{
	gv::TowerValues{150, 20, 300, 1000, {0, 0, 255}},
	gv::TowerValues{250, 30, 500, 1000, {100, 200, 100}},
	gv::TowerValues{500, 60, 200, 500, {160, 32, 250}}
};
