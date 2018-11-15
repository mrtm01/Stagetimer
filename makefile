#http://retis.sssup.it/~luca/makefiles.pdf
#OBJS specifies which files to compile as part of the project
OBJS = StageTimer.o TimeDisplay.o Timer.o CommandServer.o CommandHandeler.o Utility.o

#CC specifies which compiler we're using
CC = g++

#CXXFLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
CXXFLAGS = -Wall -ggdb3 -std=c++11

#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_ttf -lSDL2_net -pthread

#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = stagetimer

#This is the target that compiles our executable
all : $(OBJS)
	$(CC) $(OBJS) $(CXXFLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME)
clean:
	rm *.o $(OBJ_NAME)