# change application name here (executable output name)
TARGET=TypescriptDocumentGenerator

# compiler
CC=g++
# debug
DEBUG=-g
# optimisation
OPT=-O0
# warnings
WARN=-Wall
#src directory
SRCDIR=src
#object directoy
CPPVERSION=-std=c++17
OBJDIR=obj
#target directory

CCFLAGS=$(DEBUG) ${CPPVERSION} $(OPT) $(WARN) -pipe
# linker
LD=g++
LDFLAGS=$(PTHREAD)

OBJS=    $(OBJDIR)/main.o \
		 $(OBJDIR)/Directory.o\
		$(OBJDIR)/ComponentFile.o\


all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/ComponentFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/ComponentFile.cpp -o $(OBJDIR)/ComponentFile.o

$(OBJDIR)/Directory.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Directory.cpp -o $(OBJDIR)/Directory.o

$(OBJDIR)/main.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
    
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)