# 21-07-2013
# billy

EXE = prova_gplot # Executable
OBJ = prova_gplot.o gplot.o # Objectes
COM = gcc # Compilador
LIB = -lm # Llibreries (-l*, -L*, -I*)
MAC = -D_GNU_SOURCE # Macros (-D*)
AVS = -W -Wall -Wextra -ansi -pedantic # Avisos
OPT = -march=native -O3 -pipe # Optimitzacio
DEP = -g -DDEBUG # Depuracio, no recomanable junt amb $(OPT)
OPC = $(OPT) $(AVS) $(MAC) -std=c11 # Opcions
DIR = ~/bin # Directori per a instalar

all: $(EXE)

$(EXE): $(OBJ)
	@echo Enllaçant $(OBJ) per a crear $(EXE)
	$(COM) $(LIB) $(OBJ) -o $@

prova_gplot.o: prova_gplot.c gplot.h
	@echo Compilant $<
	$(COM) $(OPC) -c $<

gplot.o: gplot.c gplot.h
	@echo Compilant $<
	$(COM) $(OPC) -fPIC -c $<

exe: all
	./$(EXE)

install: all
	mkdir -p $(DIR)
	cp $(EXE) $(DIR)

install_gplot: gplot.o
	cp gplot.h /usr/local/include/gplot.h
	chown root:staff /usr/local/include/gplot.h
	ld -o libgplot.so $< -shared
	mv libgplot.so /usr/local/lib/libgplot.so
	chown root:staff /usr/local/lib/libgplot.so

clean:
	@echo Netejant...
	rm -rf $(EXE) $(OBJ) *~ *.dat
