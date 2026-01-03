ECHO = echo
GCC = g++
CCFLAGS = -pedantic -std=c++11 -Wall -g
OBJETS = Trajet.o TrajetSimple.o TrajetCompose.o TADListeTrajet.o Catalogue.o main.o
EXE = trajets
LIBS = -lm

$(EXE) : $(OBJETS)
	$(GCC) $(CCFLAGS) -o $(EXE) $(OBJETS) $(LIBS)

%.o : %.cpp %.h
	$(GCC) $(CCFLAGS) -c $<

main.o : main.cpp Trajet.h TrajetSimple.h TrajetCompose.h TADListeTrajet.h Catalogue.h
	$(GCC) $(CCFLAGS) -c $<

clean:
	rm -f *.o trajets

