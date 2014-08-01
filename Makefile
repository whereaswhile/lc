# -------------------------------------------------------------------------------------
# Change only these...
# -------------------------------------------------------------------------------------

# Program file name
PROGNAME = test

# Directories
TOP_DIR = $(shell pwd)
# Location to save output
OUT_DIR = ./

# The source files in .o format
OBJECTS = main.o

# -------------------------------------------------------------------------------------
# Static variables
# -------------------------------------------------------------------------------------

MYLIBS = 
#$(OUT_DIR)/bgapi.lib $(OUT_DIR)/ccaapi.lib
#INCLUDES = -I$(SUBLIBRARY) $(MYINCLUDES)
CV_INCLUDES = 
#-I"/cygdrive/d/Program Files/OpenCV/OpenCV210/include/opencv"
CV_LIBS = 
#-L"/cygdrive/d/Program Files/OpenCV/OpenCV210/lib"
LIBS = 
#-lcv210 -lcvaux210 -lcxcore210 -lhighgui210
INCLUDES = 
#$(CV_INCLUDES) $(MYINCLUDES)
GFLAG = -g

# -------------------------------------------------------------------------------------
# Actual make commands
# -------------------------------------------------------------------------------------

.PHONY: all
all: $(PROGNAME)
	@#mv $(PROGNAME) ./$(OUT_DIR)/
	@echo Everything compiled and ready!

%.d : %.cpp
	@echo Making dependencies for $<...
	@set -e; \
	rm -f $@; \
	gcc $(INCLUDES) -MM $< > $@.$$$$; \
	sed 's,\($*\)\.o[:]*,\1.o $@: ,g' < $@.$$$$ > $@; \
	rm -f $@.$$$$

ifneq ($(MAKECMDGOALS),clean)
-include $(OBJECTS:.o=.d)
endif

%.o : %.cpp
	@echo Compiling $<
	gcc -c $(GFLAG) $(INCLUDES) $< -o $@

$(PROGNAME): $(OBJECTS)
	@echo Linking $(PROGNAME)...
	gcc $(CV_LIBS) -Wall -o $(PROGNAME) $(OBJECTS) $(MYLIBS) $(LIBS) -lstdc++

clean:
	@echo Removing .o files and executable...
	@rm -f $(PROGNAME)
	@rm -f $(OBJECTS)
	@rm -f $(OBJECTS:.o=.d)
	@echo Done

rebuild: clean all

run: all
	@echo Running $(PROGNAME)...
	@echo
	@./$(PROGNAME)
