CXX				= clang++
CXX_FLAGS =	-Wall -Wextra -O2 -std=c++23

TARGET		= trains

SRCS			=	test.cpp
OBJS			= $(SRCS:.cpp=.o)

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXX_FLAGS) -o $@ $^

%.o: %.cpp
	$(CXX) $(CXX_FLAGS)	-c $^

clean:
	rm $(TARGET) $(OBJS)
