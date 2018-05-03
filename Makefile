# General
CC = g++

# Names and flags
INC_DIR = mavlink_c_library_v1/common
CPPSOURCES += $(wildcard *.cpp)

OBJECTS = $(CPPSOURCES:.cpp=.o)
EXECUTABLE = position_controller
CFLAGS = -c -Wall -g -I $(INC_DIR) -g -DSTANDALONE
LIBS =

all: $(CPPSOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) -pthread $(OBJECTS) -o $@ $(LIBS)

.cpp.o:
	$(CC) $(CFLAGS) -std=c++14 $(INCLUDES) $< -o $@

clean:
	@echo $OBJECTS = $(OBJECTS)
	rm -rf $(OBJECTS) $(EXECUTABLE)
