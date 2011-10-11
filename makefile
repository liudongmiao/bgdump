VERSION=v2.4
DEF=-DRTMPDUMP_VERSION=\"$(VERSION)\" -DDUMPAUDIO -DNO_CRYPTO
CFLAGS=-Wall -O2 $(DEF)
OBJS=amf.o log.o rtmp.o bgdump.o

bgdump: $(OBJS)
	$(CC) $(DEF) $(OBJS) -s -o bgdump

clean:
	rm -f $(OBJS) bgdump

amf.o: amf.c amf.h bytes.h log.h makefile
log.o: log.c log.h makefile
rtmp.o: rtmp.c rtmp.h rtmp_sys.h log.h amf.h makefile
bgdump.o: rtmp.h bible.h makefile
