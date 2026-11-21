CC      = gcc
CFLAGS  = -std=c99 -Wall -Wextra -g
TARGET  = tudengitakso
OBJS    = main.o menu.o trip.o driver.o admin.o storage.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c models.h driver.h storage.h menu.h
	$(CC) $(CFLAGS) -c main.c

menu.o: menu.c menu.h models.h trip.h driver.h admin.h storage.h
	$(CC) $(CFLAGS) -c menu.c

trip.o: trip.c trip.h models.h
	$(CC) $(CFLAGS) -c trip.c

driver.o: driver.c driver.h models.h
	$(CC) $(CFLAGS) -c driver.c

admin.o: admin.c admin.h
	$(CC) $(CFLAGS) -c admin.c

storage.o: storage.c storage.h driver.h models.h
	$(CC) $(CFLAGS) -c storage.c

run: $(TARGET)
	./$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
