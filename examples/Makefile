TARGET=maintest

LIBS=-lglib-2.0 -lgobject-2.0 -lgqpid
LIBDIR=-L../src
INCDIR=-I../src -I/usr/include/glib-2.0 -I/usr/include -I/usr/lib64/glib-2.0/include -I/usr/include/glib-2.0/gobject

all:
	gcc test2.c -g -o $(TARGET) $(INCDIR) $(LIBS) $(LIBDIR)
	gcc test3.c -g -o test3 $(INCDIR) $(LIBS) $(LIBDIR)
	gcc test4-map.c -g -o test4-map $(INCDIR) $(LIBS) $(LIBDIR)
	gcc test4-list.c -g -o test4-list $(INCDIR) $(LIBS) $(LIBDIR)
	gcc test5.c -g -o test5 $(INCDIR) $(LIBS) $(LIBDIR)
	gcc receive_list.c -g -o receive_list $(INCDIR) $(LIBS) $(LIBDIR)
