#On purge la liste des suffixes utilis� pour les r�les implicites
.SUFFIXES:

#On ajoute simplements les extensions dont l'on a besoin
.SUFFIXES:.cpp .o

#Nom de l'executable
EXEC=Projet

#Liste des fichiers sources separes par des espaces
SOURCES=main.cpp ParetoDisplay.cpp Point.cpp EnsembleDisplay.cpp Ensemble.cpp Front.cpp SquareGenerator.cpp LoaderPoint.cpp Graham.cpp Traitement.cpp Exporter.cpp

#Liste des fichiers objets
OBJETS=$(SOURCES:%.cpp=%.o)

#Compilateur et options de compilation
CCPP=g++
CFLAGS=-Wall -ansi -pedantic -ffast-math -I /usr/X11R6/include -I ./CImg -g -std=c++0x


LFLAGS= -L . -L /usr/X11R6/lib  -lpthread -lX11 -Dcimg_use_xshm  -lm 
#-lXext
#R�le explicite de construction de l'ex�utable
$(EXEC):$(OBJETS) Makefile
	$(CCPP) -o  $(EXEC) $(OBJETS) $(LFLAGS)
.cpp.o:
	$(CCPP) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJETS)
clear:
	rm $(EXEC)
depend:
	sed -e "/^#DEPENDANCIES/,$$ d" Makefile >dependances
	echo "#DEPENDANCIES" >> dependances
	$(CCPP) -MM $(SOURCES) >> dependances
	cat dependances >Makefile
	rm dependances

#DEPENDANCIES
main.o: main.cpp 
Ensemble.o : Ensemble.cpp
DisplayPareto.o : ParetoDisplay.cpp
Point.o : Point.cpp
EnsembleDisplay.o : EnsembleDisplay.cpp

