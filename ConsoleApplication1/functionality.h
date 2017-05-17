#pragma once
#include "magicParticles.h"

typedef MP(*determination_f)(const int,  MP[]);
typedef void(*determination_v)(const int,  MP[]);

void determineMPlist(const int cnt,  MP mpa[]);
MP determineMPfunc(const int cnt, MP mpa[]);