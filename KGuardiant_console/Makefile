#Makefile do proxecto, construe todos os arquivos cpp e header 
# Marzo 2014 - Javier Toja Alamancos
CC=g++
CFLAGS= -ggdb -lm -I. 
OCVFLAGS= `pkg-config --libs --cflags opencv cvblob`

all: kguardiant

kguardiant : main.o
	$(CC) -g *.o -o kguardiant $(INCLUDEFC) $(LIBSFC)  $(OCVFLAGS) 

main.o: main.cpp
	$(CC) -c *.cpp *.h $(INCLUDEFC)  $(LIBSFC) $(OCVFLAGS) 

clean:
	rm -rf *o kguardiant *.gch