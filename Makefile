# remplacer par variable interne: $(VAR)
#remplacer par variable d'env.: ${VAR}
#remplacer par cible: $@
#remplacer par première dépendance: $<
#remplacer par dépendances mises à jour // cible: $?
#remplacer par toutes les dépendances: $^ 

OBJ = main.o carte.o interface.o faction.o plateau.o 
CC = gcc -Wall -Wextra -std=c99

all: oriiflamme


#---------------------------------- LOT A ---------------------------------------
carte.o : carte.c carte.h
	$(CC) -c $<

interface.o: interface.c interface.h
	$(CC) -c $<

faction.o: faction.c faction.h
	$(CC) -c $<


plateau.o: plateau.c plateau.h faction.h carte.h
	$(CC) -c $<


main.o: main.c interface.h
	$(CC) -c $<


#---------------------------------- LOT B ---------------------------------------
struct.o: struct.c struct.h constante.h carte.h plateau.h faction.h interface.h
	$(CC) -c $<

effets.o: effets.c struct.h carte.h plateau.h faction.h
	$(CC) -c $<

#---------------------------------- FINAL ---------------------------------------
oriiflamme : $(OBJ)
	$(CC) -o $@ $^

