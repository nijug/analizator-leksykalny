a.out: main.o data.o alex.o parser.o
		$(CC) $^

main.o:
data.o: data.h
alex.o: alex.h
parser.o: alex.h fun_stack.h data.h
	
