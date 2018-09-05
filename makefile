.PHONY: outputdir
#Directory definitions.
SRCDIR := src
OBJDIR := obj
RESDIR := resources
OUTDIR := bin
#Compiler
COMPILER := g++
#Compiler options.
CFLAG := -I$(SRCDIR)
EXEC:= game.out
LIBRARIES := -lSDL2 -lSDL2_mixer -lSDL2_ttf
#Resources.
HEADERS := \
fvec2.h \
keyboard.h \
graphics/colors.h \
graphics/font.h \
screens/screen.h \
screens/screenmanager.h \
game.h src/global.h \
screens/titlescreen.h \
entities/entity.h \
entities/ball.h \
entities/player.h \
screens/levelscreen.h \
screens/gameoverscreen.h \
paraBall.h
CLASSES := \
keyboard.cpp \
graphics/font.cpp \
screens/screenmanager.cpp \
game.cpp \
global.cpp \
screens/titlescreen.cpp \
entities/player.cpp \
entities/ball.cpp \
screens/levelscreen.cpp \
screens/gameoverscreen.cpp \
paraBall.cpp \
main.cpp
RESOURCES := sfx/collision.wav sfx/cursormove.wav sfx/death.wav sfx/point.wav sfx/select.wav \
gfx/prstartk.ttf
#Objects Directory
objdir:
	if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
#Output Directory
outputdir:
	if [ ! -d $(OUTDIR) ]; then mkdir $(OUTDIR); fi
#Copying resources
$(addprefix $(OUTDIR)/,$(RESOURCES)): $(OUTDIR)/%: $(RESDIR)/% outputdir
	if [ ! -d $(dir $@) ]; then mkdir $(dir $@); fi
	cp $< $@
#Main executable
game: $(addprefix $(OBJDIR)/,$(CLASSES:.cpp=.o)) outputdir
	$(COMPILER) -o $(OUTDIR)/$(EXEC) $(filter-out outputdir,$^) $(LIBRARIES)
#Class compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	$(COMPILER) -c -o $@ $< $(CFLAG)
#Resource and app packaging
all: $(addprefix $(OUTDIR)/,$(RESOURCES)) game
#Exectuting the application
run: 
	./$(OUTDIR)/$(EXEC)
#Packing and executing
debug: all run
#Clean all outputs
clean:
	if [ -d $(OBJDIR) ]; then rm -R $(OBJDIR); fi
	if [ -d $(OUTDIR) ]; then rm -R $(OUTDIR); fi