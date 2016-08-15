INCLUDE = -I/usr/include/GL 
LIBDIR  = -L. -L/usr/X11R6/lib

COMPILERFLAGS = -Wall  
CC = g++
CFLAGS = $(COMPILERFLAGS) $(INCLUDE)
LIBRARIES = -lglut -lGL -lGLU -lXmu -lXext -lXi -lX11 -lm


all:  myLego 

canvasTest : canvasTest.o canvas.o
	$(CC) $(CFLAGS) -o canvasTest $(LIBDIR) canvas.o canvasTest.o $(LIBRARIES)  

LegoStructs : LegoStructs.o
	$(CC) $(CFLAGS) -o LegoStructs.o $(LIBDIR) -c $(LIBRARIES)

myLego : myLego.o LegoStructs.o
	$(CC) $(CFLAGS) -o myLego $(LIBDIR) LegoStructs.o myLego.o $(LIBRARIES)  

drawB : drawB.o
	$(CC) $(CFLAGS) -o drawB $(LIBDIR) lego.o drawB.o $(LIBRARIES)  
