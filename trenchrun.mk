# project name (generate executable with this name)

rm       = rm -rf
CC       = g++
# compiling flags here
CCFLAGS   = -c -Wall -g -I.

LINKER   = g++
# linking flags here
LFLAGS   =

SRCDIR   = .
OBJDIR   = ./obj

#
TARGET   = $(OBJDIR)/trenchrun
SOURCES  := \
	./Trenchrun.cpp \
	./Board.cpp \
	./Common.cpp \
	./Move.cpp \
	./MoveGenerator.cpp \
	./MoveList.cpp \
	./Output.cpp \
	./Parser.cpp \
	./MiniMax.cpp \
	./NegaMax.cpp

OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS     := $(OBJECTS:%.o=%.d)

all: $(TARGET)

run: $(TARGET)
	$(TARGET)

dbg: $(TARGET)
	gdb $(TARGET)

$(TARGET): $(OBJECTS)
	# link all the objects files
	@echo "Linking..."
	$(LINKER) -o $(TARGET) $(LFLAGS) $(OBJECTS)

# include all .d files
-include $(DEPS)

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp	| $(OBJDIR)
	@echo "Compiling "$<"..."
	$(CC) $(CCFLAGS) -MMD -c $< -o $@

clean:
	@echo "Cleanup..."
	@$(rm) $(OBJDIR)


$(OBJDIR):
	mkdir $(OBJDIR)
