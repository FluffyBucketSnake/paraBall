.PHONY: clean

#Directory definitions.
SRCDIR := src
OBJDIR := obj
RESDIR := resources
OUTDIR := bin

#Compiler
COMPILER := g++
#Compiler options.
CFLAG := -I$(SRCDIR)
LIBRARIES := -lSDL2 -lSDL2_mixer -lSDL2_ttf

#Tools
RM := rm -R
MKDIR := mkdir -p
CP := cp

#Inputs.
HEADERS := $(wildcard $(SRCDIR)/*.h) $(wildcard $(SRCDIR)/**/*.h)
SOURCES := $(wildcard $(SRCDIR)/*.cpp) $(wildcard $(SRCDIR)/**/*.cpp)
RESOURCES_IN := $(wildcard $(RESDIR)/*.*) $(wildcard $(RESDIR)/**/*.*)

#Outputs.
OBJECTS := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
RESOURCES_OUT := $(RESOURCES_IN:$(RESDIR)/%=$(OUTDIR)/%)
BINARY:= $(OUTDIR)/paraBall.out

#Cleaning.
clean:
	$(RM) $(OBJDIR) ; \
	$(RM) $(OUTDIR)

#Folders.
$(OBJDIR)/.:
	$(MKDIR) $@
$(OBJDIR)%/.:
	$(MKDIR) $@
$(OUTDIR)/.:
	$(MKDIR) $@
$(OUTDIR)%/.:
	$(MKDIR) $@

.SECONDEXPANSION:

#Compile objects.
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)/.
	$(COMPILER) -c $< -o $@ $(CFLAG)

#Link executable.
$(BINARY): $(OBJECTS) $(HEADERS) | $$(@D)/.
	$(COMPILER) $(OBJECTS) -o $@ $(CFLAG) $(LIBRARIES)

#Copy resources.
$(OUTDIR)/% : $(RESDIR)/% | $$(@D)/.
	$(CP) $< $@

#Build game.
all: $(BINARY) $(RESOURCES_OUT)

debug: CFLAG+=-g
debug: all

#Run executable
run: all
	./$(BINARY)