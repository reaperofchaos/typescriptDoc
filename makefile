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
		 $(OBJDIR)/Component.o\
		 $(OBJDIR)/ComponentFileCreator.o\
		 $(OBJDIR)/FileType.o\
		 ${OBJDIR}/ReducerFile.o\
		 ${OBJDIR}/SelectorFile.o\
		 ${OBJDIR}/SagaFile.o\
		 ${OBJDIR}/ReactComponentFile.o\
		 $(OBJDIR)/TypeFile.o\
		 $(OBJDIR)/EnumType.o\
		 $(OBJDIR)/Property.o\
		 ${OBJDIR}/InterfaceType.o\
		 ${OBJDIR}/ImportType.o\



all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(LDFLAGS)

$(OBJDIR)/ImportType.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Element/ImportType.cpp -o $(OBJDIR)/ImportType.o

$(OBJDIR)/InterfaceType.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Element/InterfaceType.cpp -o $(OBJDIR)/InterfaceType.o

$(OBJDIR)/Property.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Element/Property.cpp -o $(OBJDIR)/Property.o

$(OBJDIR)/EnumType.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Element/EnumType.cpp -o $(OBJDIR)/EnumType.o

$(OBJDIR)/SagaFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/SagaFile.cpp -o $(OBJDIR)/SagaFile.o

$(OBJDIR)/SelectorFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/SelectorFile.cpp -o $(OBJDIR)/SelectorFile.o

$(OBJDIR)/ReducerFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/ReducerFile.cpp -o $(OBJDIR)/ReducerFile.o

$(OBJDIR)/TypeFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/TypeFile.cpp -o $(OBJDIR)/TypeFile.o

$(OBJDIR)/ReactComponentFile.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/ReactComponentFile.cpp -o $(OBJDIR)/ReactComponentFile.o

$(OBJDIR)/FileType.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/FileType.cpp -o $(OBJDIR)/FileType.o

$(OBJDIR)/ComponentFileCreator.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/FileTypes/ComponentFileCreator.cpp -o $(OBJDIR)/ComponentFileCreator.o

$(OBJDIR)/Component.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Component.cpp -o $(OBJDIR)/Component.o

$(OBJDIR)/Directory.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/Directory.cpp -o $(OBJDIR)/Directory.o

$(OBJDIR)/main.o:
	$(CC) -c $(CCFLAGS) $(SRCDIR)/main.cpp -o $(OBJDIR)/main.o
    
clean:
	rm -rf $(OBJDIR)/*.o $(TARGET)