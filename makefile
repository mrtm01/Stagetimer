
#OBJS specifies which files to compile as part of the project
OBJS = StageTimer.cpp TimeDisplay.cpp Timer.cpp CommandServer.cpp CommandHandeler.cpp

#CC specifies which compiler we're using
CC = g++

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -O2 -g -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_net -pthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = stagetimer

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)