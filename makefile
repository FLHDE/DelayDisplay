# VC6 makefile

PLUGIN_NAME = DelayDisplay

COMMON_DEF = Common.def
COMMON_LIB = Common.lib

CXX_FLAGS = /c /O2 /nologo /W3 /WX /LD /MD
LD_FLAGS = /DLL /FILEALIGN:512 /NOLOGO /RELEASE
LIB_FLAGS = /NOLOGO /MACHINE:IX86
RC_FLAGS = /nologo

$(PLUGIN_NAME).dll: Main.obj $(COMMON_LIB) makefile
    link Main.obj $(COMMON_LIB) $(LD_FLAGS) /OUT:$(PLUGIN_NAME).dll

$(PLUGIN_NAME).obj: Main.c makefile
    cl $(CXX_FLAGS) Main.c

$(COMMON_LIB): $(COMMON_DEF) Common.h makefile
    lib $(LIB_FLAGS) /def:$(COMMON_DEF) /name:COMMON /out:$(COMMON_LIB)

# Main.res: $(PLUGIN_NAME).rc makefile
#     rc /fo $(PLUGIN_NAME).res $(PLUGIN_NAME).rc

clean:
    del *.dll *.obj *.RES *.lib *.exp
