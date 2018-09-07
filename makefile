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
HEADERS := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/**/*.h)
CLASSES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/**/*.cpp)
OBJECTS := $(CLASSES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RESOURCES := $(wildcard $(RESDIR)/*.*) $(wildcard $(RESDIR)/**/*.*)
#Objects Directory
objdir:
	if [ ! -d $(OBJDIR) ]; then mkdir $(OBJDIR); fi
#Output Directory
outputdir:
	if [ ! -d $(OUTDIR) ]; then mkdir $(OUTDIR); fi
#Copying resources
$(RESOURCES:$(RESDIR)/%=$(OUTDIR)/%): $(OUTDIR)/%: $(RESDIR)/% outputdir
	if [ ! -d $(dir $@) ]; then mkdir $(dir $@); fi
	cp $< $@
#Main executable
game: $(OBJECTS) outputdir
	$(COMPILER) -o $(OUTDIR)/$(EXEC) $(OBJECTS) $(LIBRARIES)
#Class compilation
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(HEADERS)
	$(COMPILER) -c -o $@ $< $(CFLAG)
#Resource and app packaging
all: $(RESOURCES:$(RESDIR)/%=$(OUTDIR)/%) game
#Exectuting the application
run: 
	./$(OUTDIR)/$(EXEC)
#Packing and executing
debug: all run
#Clean all outputs
clean:
	if [ -d $(OBJDIR) ]; then rm -R $(OBJDIR); fi
	if [ -d $(OUTDIR) ]; then rm -R $(OUTDIR); fi