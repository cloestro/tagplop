

CC=gcc
INSTDIR=/usr/share/tagplop

CFLAGS=-g -W -Wall `pkg-config --cflags gtk+-2.0 libglade-2.0 taglib` -DFILENAME=\"$(INSTDIR)/tagplop.glade\"
LIBS=`pkg-config --libs gtk+-2.0 libglade-2.0` -ltag_c

TARGET=tagplop
OBJECTS=main.o functions.o



$(TARGET): $(OBJECTS) 
	$(CC) -o $@ $^ $(LIBS)

MAIN: main.c
	$(CC) -c $^ $(CFLAGS)

FUNCTIONS: functions.c functions.h
	$(CC) -c functions.c $(CFLAGS)
clean:
	rm -f *.o *~ $(TARGET) *.bak

install:
	mkdir -p $(INSTDIR) && \
	cp tagplop.glade $(INSTDIR)/. && \
	cp tagplop /usr/bin/.

uninstall:
	rm /usr/bin/tagplop && rm -rf $(INSTDIR)

