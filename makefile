COMPILER=g++

SRCDIR=src
OBJDIR=obj
CFLAG=-I$(SRCDIR) -I.
OUTPUT=bin/game.out
LIBRARIES=-lSDL2 -lSDL2_mixer -lSDL2_ttf

HEADERS= \
src/fvec2.h \
src/keyboard.h \
src/graphics/colors.h \
src/graphics/font.h \
src/screens/screen.h \
src/screens/screenmanager.h \
src/game.h src/global.h \
src/screens/titlescreen.h \
src/entities/entity.h \
src/entities/ball.h \
src/entities/player.h \
src/screens/levelscreen.h \
src/screens/gameoverscreen.h \
src/paraBall.h
OBJECTS= \
obj/keyboard.o \
obj/graphics/font.o \
obj/screens/screenmanager.o \
obj/game.o \
obj/global.o \
obj/screens/titlescreen.o \
obj/entities/player.o \
obj/entities/ball.o \
obj/screens/levelscreen.o \
obj/screens/gameoverscreen.o \
obj/paraBall.o \
obj/main.o

$(OBJDIR)/%.o : $(SRCDIR)/%.cpp $(HEADERS)
	$(COMPILER) -c -o $@ $< $(CFLAG)

game: $(OBJECTS)
	$(COMPILER) -o $(OUTPUT) $(OBJECTS) $(LIBRARIES)

all: game

run: 
	./$(OUTPUT)

debug: game
	./$(OUTPUT)

clean:
	rm -R $(OBJDIR); \
	mkdir $(OBJDIR) $(OBJDIR)/entities $(OBJDIR)/screens $(OBJDIR)/graphics