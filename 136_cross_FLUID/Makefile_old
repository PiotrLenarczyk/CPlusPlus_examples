#
#	FLTK-CONFIG based generic Makefile
#	Windows installation of FLTK:
#		-install Git Bash ("Git for Windows")
#		-install minGW64 -> additionally install in GUI: 
#			-MinGW->MinGW Autotools: "mingw32-automake"
#			-MSYS->MSYS Base System: "msys-make-bin"
#		-create symbolic link for git bash (make command)
#			-cmd->run with administrative priviliges
#				#cd C:\MinGW\bin
#				#mklink make.exe ..\msys\1.0\bin\make.exe
#		-run shell script in git bash
#			#./RUN_COMMANDS.sh
#	Unix does not require additional actions.

ifeq '$(OS)' "Windows_NT"
EXEEXT = .exe
endif

FLTK_PATH	 = fltk
FLTKCONFIG   = ${FLTK_PATH}/fltk-config
CXX          = $(shell $(FLTKCONFIG) --cxx)
CXXFLAGS     = $(shell $(FLTKCONFIG) --cxxflags) -Wall -I. -fmax-errors=3
LINKFLTK     = $(shell $(FLTKCONFIG) --ldstaticflags)
LINKFLTK_GL  = $(shell $(FLTKCONFIG) --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell $(FLTKCONFIG) --use-images --ldstaticflags)
LINKFLTK_ALL = $(shell $(FLTKCONFIG) --use-images --use-gl --ldstaticflags)
.SUFFIXES: .cxx .h .fl .o $(EXEEXT)

# COMPILATION FOR DEBUG
.cxx.o:
	@echo "*** Compile $<..."
	$(CXX) -I.. $(CXXFLAGS) -g -c $< -o $@

# LINKING
.o$(EXEEXT):
	@echo "*** Linking $@..."
	$(CXX) $< $(LINKFLTK) $(LINKFLTK_ALL) -o $@

# RUN EXECUTABLE WITH DEBUG STRINGS
# 	./@$

# DEBUG EXECUTABLE
#	gdb @$

