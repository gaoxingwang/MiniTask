#all:main.c parse.c parse.h
#	gcc -g main.c parse.c parse.h -o TestConf
#
#clean:
#	rm -rf ./*.o TestConf

LIBS= 
CFLAGS= -Wall -g

OBJS= main.o parse.o

main: $(OBJS)
	    gcc -o TestConf $(OBJS) $(LIBS)

clean:
	rm -rf ./*.o TestConf
