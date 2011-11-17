if BUILD_EXAMPLES
AM_CFLAGS = $(GLIB_CFLAGS) $(GOBJECT_CFLAGS) -I../src

bin_PROGRAMS = test2 test3 test4-map test4-list test5 receive_list

test2_SOURCES = test2.c
test2_LDADD = ../src/libgqpid.la
test2_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)

test3_SOURCES = test3.c
test3_LDADD = ../src/libgqpid.la
test3_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)

test4_map_SOURCES = test4-map.c
test4_map_LDADD = ../src/libgqpid.la
test4_map_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)

test4_list_SOURCES = test4-list.c
test4_list_LDADD = ../src/libgqpid.la
test4_list_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)

test5_SOURCES = test5.c
test5_LDADD = ../src/libgqpid.la
test5_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)

receive_list_SOURCES = receive_list.c
receive_list_LDADD = ../src/libgqpid.la
receive_list_LDFLAGS = $(GLIB_LIBS) $(GOBJECT_LIBS)
endif
