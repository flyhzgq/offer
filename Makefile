CC=gcc
LD=ld

CFLAGS=-Wall
LDFLAGS=-Wall -lm

TARGET=offer

all: $(TARGET)

OBJS=offer.o array.o stack.o queue.o tree.o sort.o

$(TARGET): $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

clean: 
	-rm *.o offer