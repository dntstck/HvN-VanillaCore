CPP = clang++-devel
INCLUDE= -I../../../../Internal/liblua/include -I../../../../Internal/liblua/src
LIBDIR=../../../../Internal/liblua/lib
LIBS=-llua -llualib

DTARGET = qc_dbg
RTARGET = qc_rel
DOBJDIR = debug
ROBJDIR = release
$(shell if [ ! -d $(DOBJDIR) ]; then mkdir $(DOBJDIR); fi)
$(shell if [ ! -d $(ROBJDIR) ]; then mkdir $(ROBJDIR); fi)

CFLAGS = -Wall -D_THREAD_SAFE -pipe -msse2 -mssse3 -m32 -std=c++1z -stdlib=libc++ -Wno-invalid-source-encoding
#debug
CFLAGS_DBG = $(CFLAGS)
CLINKFLAGS_DBG = $(CFLAGS_DBG)
CFLAGS_DBG += -g3 -O0 -ggdb -DNDEBUG -fexceptions -fstandalone-debug
#CLINKFLAGS_DBG += -fsanitize=address,undefined -fsanitize-recover=all

#release
CFLAGS_REL = $(CFLAGS)
CLINKFLAGS_REL = $(CFLAGS_REL)
CFLAGS_REL += -Ofast -g0 -fexceptions
#CLINKFLAGS_REL += -flto

CPPFILES := $(wildcard *.cpp)
OBJ_DBG_FILES := $(addprefix debug/,$(notdir $(CPPFILES:.cpp=.o)))
OBJ_REL_FILES := $(addprefix release/,$(notdir $(CPPFILES:.cpp=.o)))

DCPPOBJS        = $(CPPFILE:%.cpp=$(DOBJDIR)/%.o)
RCPPOBJS        = $(CPPFILE:%.cpp=$(ROBJDIR)/%.o)

all: $(DTARGET) $(RTARGET)
debug: $(DTARGET)
release: $(RTARGET)

$(DTARGET): $(OBJ_DBG_FILES)
	$(CPP) $(CLINKFLAGS_DBG) $(INCLUDE) -L$(LIBDIR) $(OBJ_DBG_FILES) $(LIBS) -o $(DTARGET)

$(RTARGET): $(OBJ_REL_FILES)
	$(CPP) $(CLINKFLAGS_REL) $(INCLUDE) -L$(LIBDIR) $(OBJ_REL_FILES) $(LIBS) -o $(RTARGET)

$(DOBJDIR)/%.o: %.cpp
	@echo $(CPP) $(CFLAGS_DBG) -c $< $(INCLUDE) -L$(LIBDIR) -o $@
	$(CPP) $(CFLAGS_DBG) -c $< $(INCLUDE) -L$(LIBDIR) -o $@

$(ROBJDIR)/%.o: %.cpp
	@echo $(CPP) $(CFLAGS_REL) -c $< $(INCLUDE) -L$(LIBDIR) -o $@
	$(CPP) $(CFLAGS_REL) -c $< $(INCLUDE) -L$(LIBDIR) -o $@

clean:
	rm -f $(OBJ_DBG_FILES) $(OBJ_REL_FILES) $(DTARGET) $(RTARGET)
