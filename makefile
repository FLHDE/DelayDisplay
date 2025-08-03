# VC6 makefile

PLUGIN_NAME = DelayDisplay

COMMON_DEF = Common.def
COMMON_LIB = Common.lib

RC_FILE = Main.rc
RES_FILE = Main.RES

CXX_FLAGS = /c /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /FILEALIGN:512 /NOLOGO /RELEASE
LIB_FLAGS = /NOLOGO /MACHINE:IX86
RC_FLAGS = /nologo

$(PLUGIN_NAME).dll: Main.obj $(RES_FILE) $(COMMON_LIB) makefile
    link Main.obj $(COMMON_LIB) $(RES_FILE) $(LD_FLAGS) /OUT:$(PLUGIN_NAME).dll

$(PLUGIN_NAME).obj: Main.cpp makefile
    cl $(CXX_FLAGS) Main.cpp

$(COMMON_LIB): $(COMMON_DEF) Common.h makefile
    lib $(LIB_FLAGS) /def:$(COMMON_DEF) /name:COMMON /out:$(COMMON_LIB)

$(RES_FILE): $(RC_FILE) makefile
    rc /fo $(RES_FILE) $(RC_FILE)

clean:
    del *.dll *.obj *.RES *.lib *.exp
