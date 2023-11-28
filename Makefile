#############################################################################
# Makefile for building: BerryCC
# Generated by qmake (1.07a) (Qt 3.3.7) on: Thu Jan 18 17:52:54 2007
# Project:  BerryCC.pro
# Template: app
# Command: $(QMAKE) -o Makefile BerryCC.pro
#############################################################################

####### Compiler, tools and options

CC       = gcc
CXX      = g++
LEX      = flex
YACC     = yacc
CFLAGS   = -pipe -Wall -W -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i386 -mtune=generic -fasynchronous-unwind-tables  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
CXXFLAGS = -pipe -Wall -W -O2 -g -pipe -Wall -Wp,-D_FORTIFY_SOURCE=2 -fexceptions -fstack-protector --param=ssp-buffer-size=4 -m32 -march=i386 -mtune=generic -fasynchronous-unwind-tables  -DQT_NO_DEBUG -DQT_SHARED -DQT_THREAD_SUPPORT
LEXFLAGS = 
YACCFLAGS= -d
INCPATH  = -I/usr/lib/qt-3.3/mkspecs/default -I. -I$(QTDIR)/include -I.ui/ -I. -I.moc/
LINK     = g++
LFLAGS   = 
LIBS     = $(SUBLIBS) -L$(QTDIR)/lib -lqt-mt -lXext -lX11 -lm
AR       = ar cqs
RANLIB   = 
MOC      = $(QTDIR)/bin/moc
UIC      = $(QTDIR)/bin/uic
QMAKE    = qmake
TAR      = tar -cf
GZIP     = gzip -9f
COPY     = cp -f
COPY_FILE= $(COPY)
COPY_DIR = $(COPY) -r
INSTALL_FILE= $(COPY_FILE)
INSTALL_DIR = $(COPY_DIR)
DEL_FILE = rm -f
SYMLINK  = ln -sf
DEL_DIR  = rmdir
MOVE     = mv -f
CHK_DIR_EXISTS= test -d
MKDIR    = mkdir -p

####### Output directory

OBJECTS_DIR = .obj/

####### Files

HEADERS = 
SOURCES = main.cpp
OBJECTS = .obj/main.o \
		.obj/berry_control_centre.o \
		.obj/qmake_image_collection.o
FORMS = berry_control_centre.ui
UICDECLS = .ui/berry_control_centre.h
UICIMPLS = .ui/berry_control_centre.cpp
SRCMOC   = .moc/moc_berry_control_centre.cpp
OBJMOC = .obj/moc_berry_control_centre.o
DIST	   = BerryCC.pro
QMAKE_TARGET = BerryCC
DESTDIR  = 
TARGET   = BerryCC

first: all
####### Implicit rules

.SUFFIXES: .c .o .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o $@ $<

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o $@ $<

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(UICDECLS) $(OBJECTS) $(OBJMOC)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJMOC) $(OBJCOMP) $(LIBS)

mocables: $(SRCMOC)
uicables: $(UICDECLS) $(UICIMPLS)

$(MOC): 
	( cd $(QTDIR)/src/moc && $(MAKE) )

Makefile: BerryCC.pro  /usr/lib/qt-3.3/mkspecs/default/qmake.conf /usr/lib/qt-3.3/lib/libqt-mt.prl
	$(QMAKE) -o Makefile BerryCC.pro
qmake: 
	@$(QMAKE) -o Makefile BerryCC.pro

dist: 
	@mkdir -p .obj/BerryCC && $(COPY_FILE) --parents $(SOURCES) $(HEADERS) $(FORMS) $(DIST) .obj/BerryCC/ && $(COPY_FILE) --parents display.png krfb.png mycomputer.png .obj/BerryCC/ && $(COPY_FILE) --parents berry_control_centre.ui.h .obj/BerryCC/ && ( cd `dirname .obj/BerryCC` && $(TAR) BerryCC.tar BerryCC && $(GZIP) BerryCC.tar ) && $(MOVE) `dirname .obj/BerryCC`/BerryCC.tar.gz . && $(DEL_FILE) -r .obj/BerryCC

mocclean:
	-$(DEL_FILE) $(OBJMOC)
	-$(DEL_FILE) $(SRCMOC)

uiclean:
	-$(DEL_FILE) $(UICIMPLS) $(UICDECLS)

yaccclean:
lexclean:
clean: mocclean uiclean
	-$(DEL_FILE) $(OBJECTS)
		-$(DEL_FILE) .ui/qmake_image_collection.cpp
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) $(TARGET)


FORCE:

####### Compile

.obj/main.o: main.cpp .ui/berry_control_centre.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/main.o main.cpp

.ui/berry_control_centre.h: berry_control_centre.ui 
	$(UIC) berry_control_centre.ui -o .ui/berry_control_centre.h

.ui/berry_control_centre.cpp: .ui/berry_control_centre.h berry_control_centre.ui berry_control_centre.ui.h 
	$(UIC) berry_control_centre.ui -i berry_control_centre.h -o .ui/berry_control_centre.cpp

.obj/berry_control_centre.o: .ui/berry_control_centre.cpp berry_control_centre.ui.h \
		.ui/berry_control_centre.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/berry_control_centre.o .ui/berry_control_centre.cpp

.obj/moc_berry_control_centre.o: .moc/moc_berry_control_centre.cpp  .ui/berry_control_centre.h 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/moc_berry_control_centre.o .moc/moc_berry_control_centre.cpp

.moc/moc_berry_control_centre.cpp: $(MOC) .ui/berry_control_centre.h
	$(MOC) .ui/berry_control_centre.h -o .moc/moc_berry_control_centre.cpp

.obj/qmake_image_collection.o: .ui/qmake_image_collection.cpp
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o .obj/qmake_image_collection.o .ui/qmake_image_collection.cpp

.ui/qmake_image_collection.cpp: display.png \
		krfb.png \
		mycomputer.png
	$(UIC)  -embed BerryCC display.png krfb.png mycomputer.png -o .ui/qmake_image_collection.cpp

####### Install

install:  

uninstall:  

