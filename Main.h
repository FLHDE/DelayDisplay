#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#define IMPORT __declspec(dllimport)
#define NAKED __declspec(naked)

#include "Common.h"

typedef IObjRW* (*GetPlayerIObjRWFunc)();
