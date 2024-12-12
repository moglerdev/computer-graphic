INCLUDE = -I"../glm"

# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g $(INCLUDE)

# Libraries
LIBS = -lGL -lGLU -lglut

# Windows-specific paths
WIN_LIBS = -L"..\freeglut\lib\x64" -lfreeglut -lopengl32 -lglu32
WIN_INCLUDE = -I"..\freeglut\include"

# Source and output files
SRCS = $(wildcard *.cpp *.c)
OBJS = $(SRCS:.cpp=.o)
TARGET = uebung4.bin

# Detect Windows
ifeq ($(OS),Windows_NT)
    CXXFLAGS += $(WIN_INCLUDE)
    LIBS = $(WIN_LIBS)
	TARGET = uebung4.exe
endif

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@


# Define DEL based on the operating system
ifeq ($(OS),Windows_NT)
    DEL = del /Q
else
    DEL = rm -f
endif

clean:
	$(DEL) $(OBJS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
