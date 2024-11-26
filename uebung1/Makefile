# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

# Libraries
LIBS = -lGL -lGLU -lglut

# Windows-specific paths
WIN_LIBS = -L"..\freeglut\lib\x64" -lfreeglut -lopengl32 -lglu32
WIN_INCLUDE = -I"..\freeglut\include"

# Source and output files
SRCS = $(wildcard *.cpp *.c)
OBJS = $(SRCS:.cpp=.o)
TARGET = uebung2.bin
# Static linking specific flags (ensure we don't link dynamically)
LDFLAGS = -static

# Detect Windows
ifeq ($(OS),Windows_NT)
    CXXFLAGS += $(WIN_INCLUDE)
    LIBS = $(WIN_LIBS)
	TARGET = uebung2.exe
endif

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

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