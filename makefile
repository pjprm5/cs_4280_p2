CC = gcc
CFLAGS = -g
TARGET = scanner
OBJS = main.o scanner.o
$(TARGET): $(OBJS)
	$(CC) -o $(TARGET) $(OBJS)
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
scanner.o: scanner.c
	$(CC) $(CFLAGS) -c scanner.c
clean:
	/bin/rm -f *.o $(TARGET)
