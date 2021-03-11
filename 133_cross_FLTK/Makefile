ifeq '$(OS)' "Windows_NT"
EXEEXT = .exe
endif

FLTK_PATH	 = fltk
FLTKCONFIG   = ${FLTK_PATH}/fltk-config
CXX          = $(shell $(FLTKCONFIG) --cxx)
CXXFLAGS     = $(shell $(FLTKCONFIG) --cxxflags) -Wall -I. -fmax-errors=3
LINKFLTK     = $(shell $(FLTKCONFIG) --libs --ldstaticflags)
LINKFLTK_GL  = $(shell $(FLTKCONFIG) --libs --use-gl --ldstaticflags)
LINKFLTK_IMG = $(shell $(FLTKCONFIG) --libs --use-images --ldstaticflags)
LINKFLTK_ALL = $(shell $(FLTKCONFIG) --libs --use-images --use-gl --ldstaticflags) 
.SUFFIXES:  .cpp .cxx .h .fl .o $(EXEEXT)

# COMPILATION AND LINKING FOR DEBUG
.cxx .cpp:
	rm -f $@ $@.o
	@echo "*** Compile $<..."
	$(CXX) $< -I.. $(CXXFLAGS) -g -c -o $@.o
	@echo "*** Linking $@.o..."
	$(CXX) $@.o $(LINKFLTK_ALL) -o $@


## RUN EXECUTABLE WITH DEBUG STRINGS
## 	./@$

## DEBUG EXECUTABLE
##	gdb @$


