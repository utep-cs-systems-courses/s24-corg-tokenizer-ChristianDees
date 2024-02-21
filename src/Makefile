OBJS = tokenizer.o history.o uimain.o

CFLAGS = -g -O3

all: myProgram

myProgram: $(OBJS)
	cc -o myProgram $(CFLAGS) $(OBJS)

$(OBJS): tokenizer.h history.h

clean:

	rm -f *.c# *.c~ *.o myProgram

run:myProgram
	./myProgram
