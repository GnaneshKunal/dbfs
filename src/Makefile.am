noinst_LTLIBRARIES = libdb.la
libdb_la_SOURCES = \
	utils.h	\
	db.h	\
	db.c

bin_PROGRAMS = dbfs
dbfs_SOURCES = main.c
dbfs_CPPFLAGS = -I$(top_srcdir)/src
dbfs_LDADD = libdb.la
