

CC=gcc
INSTDIR=/usr/share/tagplop
# -DFILENAME=\"$(INSTDIR)/tagplop.glade\"
CFLAGS=-g `pkg-config --cflags gtk+-2.0 libglade-2.0 taglib` `xml2-config --cflags`
LIBS=`pkg-config --libs gtk+-2.0 libglade-2.0` `xml2-config --libs` -ltag_c -ltunepimp -lcurl

TARGET=tagplop
OBJECTS=main.o functions.o network.o xml.o gtkchosentrack.o


all: $(TARGET)


$(TARGET): $(OBJECTS) 
	$(CC) -o $@ $^ $(LIBS)

MAIN: main.c version.h functions.h xml.h
	$(CC) -c $^ $(CFLAGS)

FUNCTIONS: functions.c functions.h network.h version.h xml.h
	$(CC) -c functions.c $(CFLAGS)

networks: network.c network.h version.h
	$(CC) -c network.c $(CFLAGS)

gtkchosentrack: gtkchosentrack.c gtkchosentrack.h xml.c xml.h version.h
	$(CC) -c gtkchosentrack.c $(CFLAGS)


xml: xml.c xml.h version.h
	$(CC) -c xml.c $(CFLAGS)


clean:
	rm -f *.o *~ $(TARGET) *.bak

install:
	mkdir -p $(INSTDIR) && \
	cp tagplop.glade $(INSTDIR)/. && \
	cp tagplop /usr/bin/.

uninstall:
	rm /usr/bin/tagplop && rm -rf $(INSTDIR)

