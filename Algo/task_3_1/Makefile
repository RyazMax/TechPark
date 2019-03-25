CC := g++
CFLAGS := -Wall
OBJS := listgraph.o matrixgraph.o setgraph.o arcgraph.o

ifeq ($(mode), release)
	CFLAGS += -DNDEBUG
endif

main.out : main.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

test : test.o $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o : %.cpp *.hpp
	$(CC) -c $<

clean :
	$(RM) *.out *.o