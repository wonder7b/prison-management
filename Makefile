CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99
TARGET = prison
OBJS = main.o detenu.o cellule.o incident.o statistiques.o

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

main.o: main.c detenu.h cellule.h incident.h statistiques.h
	$(CC) $(CFLAGS) -c main.c

detenu.o: detenu.c detenu.h cellule.h
	$(CC) $(CFLAGS) -c detenu.c

cellule.o: cellule.c cellule.h
	$(CC) $(CFLAGS) -c cellule.c

incident.o: incident.c incident.h
	$(CC) $(CFLAGS) -c incident.c

statistiques.o: statistiques.c detenu.h cellule.h incident.h
	$(CC) $(CFLAGS) -c statistiques.c

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: clean
