a.out: main.o data.o fun_stack.o alex.o parser.o
		$(CC) $^

main.o: data.h
data.o: data.h
fun_stack.o: fun_stack.h
alex.o: alex.h
parser.o: parser.h
	
