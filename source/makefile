HDIR = /home/tomer/scripts/C_projects/carGame_Version/Headers
ODIR = Obj
CC = gcc
CFLAGS = -I/$(HDIR) -lncurses
DEPS = $(HDIR)/carGameGraphics.h $(HDIR)/carGameMechanics.h
_OBJ = main.o carGameMechanics.o carGameGraphics.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))

$(ODIR)/%.o : %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

carGame: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)
