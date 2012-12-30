CFLAGS?=-Wall -Os
LDFLAGS?=-static
vh400:	 vh400.o 
install: vh400
	strip vh400
	mkdir -p $(DESTDIR)/$(PREFIX)/bin
	cp -p vh400 $(DESTDIR)/$(PREFIX)/bin
clean:
	rm -f *.o vh400
