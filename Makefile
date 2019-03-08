CC=gcc
LD=ld

CFLAGS=-Wall
LDFLAGS=-Wall

TARGET=offer

all: $(TARGET)

OBJS=offer.o array.o stack.o queue.o tree.o sort.o

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean: 
	-rm *.o offer