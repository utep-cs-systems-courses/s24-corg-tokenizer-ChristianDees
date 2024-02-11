OBJS = tokenizer.o history.o uimain.o

CFLAGS = -g -O3

all: myProgram

myProgram: $(OBJS)
	cc -o myProgram $(CFLAGS) $(OBJS)

$(OBJS): tokenizer.h history.h

clean:
	rm -f *.o myProgram

run:myProgram
	./myProgram
