TARGET=maintest

LIBS=-lglib-2.0 -lgobject-2.0 -lqpidmessaging
LLIBS =-L.
INCDIR=-I. -I/usr/include/glib-2.0 -I/usr/include -I/usr/lib64/glib-2.0/include -I/usr/include/glib-2.0/gobject -I/usr/include/qpid

all:
	g++ -g -o gqpidsession.o -c -fPIC gqpidsession.cpp $(INCDIR)
	g++ -g -o gqpidconnection.o -c -fPIC gqpidconnection.cpp $(INCDIR)
	g++ -g -o gqpidsender.o -c -fPIC gqpidsender.cpp $(INCDIR)
	g++ -g -o gqpidreceiver.o -c -fPIC gqpidreceiver.cpp $(INCDIR)
	g++ -g -o gqpidmessage.o -c -fPIC gqpidmessage.cpp $(INCDIR)
	g++ -g -o libgqpid.so --shared -fPIC gqpidsession.o gqpidconnection.o gqpidsender.o gqpidmessage.o gqpidreceiver.o $(LLIBS) $(LIBS)


clean:
	rm *.o *.so
