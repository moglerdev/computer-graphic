# Compiler and flags
CXX = g++
CXXFLAGS = -Wall -std=c++11 -g

# Libraries
LIBS = -lGL -lGLU -lglut


# Source and output files
SRCS = $(wildcard *.cpp *.c) # Automatically include all .cpp and .c files
OBJS = $(SRCS:.cpp=.o)
TARGET = uebung2.bin

# Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
