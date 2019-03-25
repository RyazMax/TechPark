main.out : main.o
	g++ -o main.out main.o

%.o : %.cpp *.hpp
	g++ -c $@ $<