AM_CXXFLAGS = $(GLIB_CFLAGS) $(GOBJECT_CFLAGS)

lib_LTLIBRARIES = libgqpid.la

libgqpid_la_SOURCES = gqpidconnection.cpp  gqpidmessage.cpp  gqpidreceiver.cpp  gqpidsender.cpp  gqpidsession.cpp
# Increment version-info for soname bump
libgqpid_la_LDFLAGS = $(QPID_LIBS) $(GLIB_LIBS) $(GOBJECT_LIBS) -module -version-info "0"

pkginclude_HEADERS = gqpidconnection.h  gqpid.h  gqpidmessage.h  gqpidreceiver.h  gqpidsender.h  gqpidsession.h
