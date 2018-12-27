#Compilation variables. Compilation flags.
#for special includes copy this -I/path/for/somehting
CC=gcc
FLAGS=-Wall -lm

#File sources
SOURCES=$(wildcard *.c)
OBJECTS=$(SOURCES:.c=.o)
TARGET=main
ZIPNAME=T1_Ciferri

#Main
all: $(TARGET)
 
#
$(TARGET): $(OBJECTS)
	@$(CC) -o $@ $^

#ADT (TAD em portugues)
%.o: %.c %.h
	@$(CC) $(FLAGS) -c $<

#if no header
%.o: %.c
	@$(CC) $(FLAGS) -c $<

#clean .o and main
clean:
	@rm -f *.o $(TARGET)

#Quick clean+all
rebuild: clean all


run:
	@./$(TARGET)


##################
######CUSTOM######
##################

zip:
	zip $(ZIPNAME) *.h *.c Makefile

database:
	cp backup.db tweets.db

