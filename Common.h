#ifndef _COMMON_
#define _COMMON_

class CEquip
{

};

namespace Archetype
{
    struct Launcher
    {
        char x00[0x90];
        float refireDelay;
    };
}

class IMPORT CELauncher
{
public:
    char x00[0xC];
    Archetype::Launcher* launcherArch;
    char x10[0x40];
    float delayElapsed;

    static CELauncher* cast(CEquip* equip);
};

class IMPORT CEquipManager
{
public:
    CEquip* FindByID(unsigned short id);
};

struct CShip
{
    char x00[0xE4];
    CEquipManager equipManager;
};

struct IObjRW
{
    char x00[0x10];
    void* cobject;
};

#endif
