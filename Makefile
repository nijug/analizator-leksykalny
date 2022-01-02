a.out: main.o parser.o data.o fun_stack.o alex.o 
		$(CC) $^
main.o: data.h
parser.o: parser.h
data.o: data.h
fun_stack.o: fun_stack.h
alex.o: alex.h	
