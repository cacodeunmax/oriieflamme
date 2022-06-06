# remplacer par variable interne: $(VAR)
#remplacer par variable d'env.: ${VAR}
#remplacer par cible: $@
#remplacer par première dépendance: $<
#remplacer par dépendances mises à jour // cible: $?
#remplacer par toutes les dépendances: $^ 

OBJ = main.o carte.o interface.o faction.o plateau.o effets.o struct.o
CC = gcc -g -Wall -Wextra -std=c99

all: oriieflamme


#---------------------------------- LOT A ---------------------------------------

interface.o: interface.c interface.h 
	$(CC) -c $<

faction.o: faction.c faction.h
	$(CC) -c $<


plateau.o: plateau.c plateau.h faction.h carte.h effets.h
	$(CC) -c $<

carte.o : carte.c carte.h
	$(CC) -c $<


#---------------------------------- LOT B ---------------------------------------
struct.o: struct.c struct.h constante.h carte.h plateau.h faction.h interface.h
	$(CC) -c $<

effets.o: effets.c struct.h carte.h plateau.h faction.h
	$(CC) -c $<

#---------------------------------- FINAL ---------------------------------------

main.o: main.c interface.h 
	$(CC) -c $<


oriieflamme : $(OBJ)
	$(CC) -o $@ $^


clean : 
	rm *.o
	rm oriieflamme
