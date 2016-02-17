# Exemple de makefile un peu automatique

# compilateur 
CC = g++
# options de compilation 
CCFLAGS =-Wall -Wextra -ansi -pedantic -g -O2 -std=c++11
# options de l'edition des liens
LDFLAGS =-lm
# liste des fichiers objets 
SRC=$(wildcard *.cpp)
OBJ= $(SRC:.cpp=.o) 
#OBJ =A.o main.o B.o 
EXE =Projet

# regle finale pour la creation de l'executable
Projet:$(OBJ)
	$(CC) $(LDFLAGS) -o $@ $(OBJ)

# compiler tous les .cpp en .o
.cpp.o:
	$(CC) $(CCFLAGS) -c $<

# creation automatique des dependances
# attention : on liste tous les fichiers cpp du repertoire mais on peut affiner ;-)
dep:
	$(CC) -MM *.cpp > makefile.dep

clean:
	rm -rf $(OBJ) core *.h.gch

makefile.dep:*.cpp
	$(CC) -MM $(SRC) > $@

-include makefile.dep
