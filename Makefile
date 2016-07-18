target := inversions
C_SRCS := list.cpp main.cpp
C_OBJS := ${C_SRCS:.cpp=.o}
C_FLAGS := -ggdb
CPP := g++

all: $(target)

$(C_OBJS): $(C_SRCS)
	$(CPP) $(C_FLAGS) -c $^

$(target): $(C_OBJS)
	$(CPP) -o $@ $(C_FLAGS) $(C_OBJS)

clean:
	rm -rf $(target)
	rm -rf $(C_OBJS)
