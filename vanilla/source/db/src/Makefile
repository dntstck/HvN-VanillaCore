CC = clang++-devel
SVN_VERSION = 70220

INCDIR =
LIBDIR =
BINDIR = ..
ROBJDIR = release
DOBJDIR = debug
SRV_DIR = /usr/game
$(shell if [ ! -d lib ]; then mkdir lib; fi)
$(shell if [ ! -d $(DOBJDIR) ]; then mkdir $(DOBJDIR); fi)
$(shell if [ ! -d $(ROBJDIR) ]; then mkdir $(ROBJDIR); fi)

# Removed -fno-rtti 
CFLAGS = -Wall -D_THREAD_SAFE -pipe -msse2 -mssse3 -m32 -std=c++1z -stdlib=libc++ -Wno-invalid-source-encoding

#debug
CFLAGS_DBG = $(CFLAGS)
CLINKFLAGS_DBG = $(CFLAGS_DBG) -Wl,rpath,/usr/local/lib32/metin2
CFLAGS_DBG += -g3 -O0 -ggdb -DNDEBUG -fexceptions -fstandalone-debug
CLINKFLAGS_DBG += -fsanitize=address,undefined fsanitize-recover=all

#release
CFLAGS_REL = $(CFLAGS)
CLINKFLAGS_REL = $(CFLAGS_REL) -Wl,rpath,/usr/local/lib32/metin2
CFLAGS_REL += -Ofast -g0 -fexceptions
#CLINKFLAGS_REL += -flto

############# libthecore libs and includes
INCDIR += -I/../../libthecore/include
LIBDIR += -L../../libthecore/lib
LIBS   += -lthecore

############# libgame libs and includes
INCDIR += -I../../libgame/include
LIBDIR += -L../../libgame/lib
LIBS   += -lgame

############# libsql libs and includes
INCDIR += -I../../libsql/include
LIBDIR += -L../../libsql/lib
LIBS   += -lsql

############# libpoly libs and includes
INCDIR += -I../../libpoly/include
LIBDIR += -L../../libpoly/lib
LIBS   += -lpoly

############# mysql libs and includes
INCDIR += -I../../../extern/mysql
LIBDIR += -L../../../extern/mysql/lib
LIBS   += -lmysqlclient -lz -pthread

############# other libs and includes
INCDIR += -I../../../extern/boost

DTARGET  = $(BINDIR)/db_r$(SVN_VERSION)_debug
RTARGET = $(BINDIR)/db_r$(SVN_VERSION)_release

CPPFILES := $(wildcard *.cpp)
OBJ_DBG_FILES := $(addprefix debug/,$(notdir $(CPPFILES:.cpp=.o)))
OBJ_REL_FILES := $(addprefix release/,$(notdir $(CPPFILES:.cpp=.o)))

DCPPOBJS	= $(CPPFILE:%.cpp=$(DOBJDIR)/%.o)
RCPPOBJS	= $(CPPFILE:%.cpp=$(RRELEASE)/%.o)

default: $(DTARGET) $(RTARGET)

debug: $(DTARGET)

release: $(RTARGET)

$(DOBJDIR)/%.o: %.cpp
	@echo $(CC) $(CFLAGS_DBG) $(INCDIR) -D__SVN_VERSION__=\"$(SVN_VERSION)\" -c $< -o $@
	@$(CC) $(CFLAGS_DBG) $(INCDIR) -D__SVN_VERSION__=\"$(SVN_VERSION)\" -c $< -o $@
$(ROBJDIR)/%.o: %.cpp
	@echo $(CC) $(CFLAGS_REL) $(INCDIR) -D__SVN_VERSION__=\"$(SVN_VERSION)\" -c $< -o $@
	@$(CC) $(CFLAGS_REL) $(INCDIR) -D__SVN_VERSION__=\"$(SVN_VERSION)\" -c $< -o $@

limit_time:
	@echo update limit time
	@python update_limit_time.py

$(DTARGET): $(OBJ_DBG_FILES)
	@echo $(CC) $(CFLAGS_DBG) $(LIBDIR) $(LIBS) -o $(DTARGET)
	@$(CC) $(CFLAGS_DBG) $(LIBDIR) $(OBJ_DBG_FILES) $(LIBS) -o $(DTARGET)

$(RTARGET): $(OBJ_REL_FILES)
	@echo $(CC) $(CFLAGS_REL) $(LIBDIR) $(LIBS) -o $(RTARGET)
	@$(CC) $(CFLAGS_REL) $(LIBDIR) $(OBJ_REL_FILES) $(LIBS) -o $(RTARGET)


clean:
	@rm -f debug/*
	@rm -f release/*
	@rm -f $(BINDIR)/game_r* $(BINDIR)/conv

tag:
	ctags *.cpp *.h *.c

dep:
	touch Depend
	makedepend -f Depend $(INCDIR) -I/usr/local/include/c++/v1 -I/usr/include/c++/v1 -prelease/ $(CPPFILE) 2> /dev/null > Depend

install_dbg: $(DTARGET)
	rm -rf $(SRV_DIR)/share/db
	cp $(DTARGET) $(SRV_DIR)/share/db

install_rel: $(RTARGET)
	rm -rf $(SRV_DIR)/share/db
	cp $(RTARGET) $(SRV_DIR)/share/db

sinclude Depend
