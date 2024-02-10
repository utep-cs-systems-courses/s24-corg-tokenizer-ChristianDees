OBJS = tokenizer.o history.o uimain.o

$FLAGS =-g -03

all: myProgram

myProgram: $(OBJS)
	cc -o myProgram $(CFLAGS) $(OBJS)

$(OBJS): tokenizer.h history.h

clean:
	rm -f *.o myProgram

run:myProgram
	./myProgram
