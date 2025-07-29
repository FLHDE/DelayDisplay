#include "Main.h"

GetPlayerIObjRWFunc GetPlayerIObjRW;

char* fmtAmmo = "%d";
char* fmtDelay = "%.1f";
char* fmtAmmoAndDelay = "%d--%.1f";
char* fmtAmmoAndZeroDelay = "%d--0.0";

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void DelayDisplay(unsigned short *equipId, char* buffer, void* unk, int ammoRemaining) {
    CShip** playerShip = (CShip**) &GetPlayerIObjRW()->cobject;
    CEquipManager& equipManager = (*playerShip)->equipManager;
    CEquip* equip = equipManager.FindByID(*equipId);
    CELauncher* launcher = CELauncher::cast(equip);

    float totalDelay = launcher->launcherArch->refireDelay;

    if (ammoRemaining == -1)
    {
        if (totalDelay >= 1.0f)
        {
            float remainingDelay = totalDelay - launcher->delayElapsed;
            if (remainingDelay > 0.0f)
                sprintf(buffer, fmtDelay, remainingDelay);
            else
                strcpy(buffer, "0.0");
        }
        else
        {
            *buffer = '\0';
        }
    }
    else if (totalDelay >= 1.0f)
    {
        float remainingDelay = totalDelay - launcher->delayElapsed;
        if (remainingDelay > 0.0f)
            sprintf(buffer, fmtAmmoAndDelay, ammoRemaining, remainingDelay);
        else
            sprintf(buffer, fmtAmmoAndZeroDelay, ammoRemaining);
    }
    else
    {
        sprintf(buffer, fmtAmmo, ammoRemaining);
    }
}

void NAKED DelayDisplay_Hook()
{
    __asm {
        push ecx
        push esi
        call DelayDisplay
        pop esi
        add esp, 0x4
        pop eax
        add esp, 0x4
        add eax, 0xB
        mov ecx, [edi+0x50]
        jmp eax
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void WriteHooks()
{
    DWORD oldProtect;
    BYTE hookPatch[7];

    DWORD flBase = (DWORD) GetModuleHandleA(NULL);
    hookPatch[0] = 0xB8;
    hookPatch[5] = 0xFF;
    hookPatch[6] = 0xD0;
    *(PDWORD) &hookPatch[1] = (DWORD) &DelayDisplay_Hook;
    LPVOID hookPatchAddr = (LPVOID) (flBase + 0xDDFD5);

    HANDLE processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    VirtualProtectEx(processHandle, hookPatchAddr, sizeof(hookPatch), PAGE_EXECUTE_READWRITE, &oldProtect);
    WriteProcessMemory(processHandle, hookPatchAddr, hookPatch, sizeof(hookPatch), NULL);
    CloseHandle(processHandle);

    BYTE jmpPatch = 0x00;
    LPVOID jmpPatchAddr = (LPVOID) (flBase + 0xDDFC0);

    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    VirtualProtectEx(processHandle, jmpPatchAddr, sizeof(jmpPatch), PAGE_EXECUTE_READWRITE, &oldProtect);
    WriteProcessMemory(processHandle, jmpPatchAddr, &jmpPatch, sizeof(jmpPatch), NULL);
    CloseHandle(processHandle);

    GetPlayerIObjRW = (GetPlayerIObjRWFunc) (flBase + 0x14BAF0);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    if(fdwReason == DLL_PROCESS_ATTACH)
        WriteHooks();
    //else if(fdwReason == DLL_PROCESS_DETACH)

    return true;
}
