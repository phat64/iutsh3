CC=cc
CFLAGS=-g -p -ansi -pedantic -Wall -D_POSIX_SOURCE 

TARGET=iutsh3

INCDIR=include/
SRCDIR=src/
OBJDIR=obj/

all: iutsh3


iutsh3: ligne_commande.o environment.o error.o prompt.o interprete.o execute.o main.o
	$(CC) -o $(TARGET)    $(CFLAGS) -I$(INCDIR) $(OBJDIR)environment.o $(OBJDIR)ligne_commande.o $(OBJDIR)prompt.o $(OBJDIR)error.o $(OBJDIR)interprete.o $(OBJDIR)execute.o  $(OBJDIR)main.o 


prompt.o: $(SRCDIR)prompt.c
	$(CC) -o $(OBJDIR)prompt.o      $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)prompt.c   

error.o: $(SRCDIR)error.c
	$(CC) -o $(OBJDIR)error.o       $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)error.c

interprete.o: $(SRCDIR)interprete.c
	$(CC) -o $(OBJDIR)interprete.o  $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)interprete.c

execute.o: $(SRCDIR)execute.c
	$(CC) -o $(OBJDIR)execute.o     $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)execute.c 

main.o: $(SRCDIR)main.c
	$(CC) -o $(OBJDIR)main.o        $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)main.c

ligne_commande.o: $(INCDIR)/ligne_commande.h
	@echo $@ is found

environment.o: $(SRCDIR)environment.c
	$(CC) -o $(OBJDIR)environment.o $(CFLAGS) -I$(INCDIR) -c $(SRCDIR)environment.c 




clean:
	rm -f $(OBJDIR)environment.o $(OBJDIR)prompt.o $(OBJDIR)interprete.o
	rm -f $(OBJDIR)execute.o $(OBJDIR)main.o $(OBJDIR)error.o
	rm -f $(SRCDIR)*~
	rm -f $(OBJDIR)*~
	rm -f $(INCDIR)*~
	rm -f ./iutsh3
