CXX	= clang++-devel

DBGBIN     = ./lib/libpolyd.a
RELBIN     = ./lib/libpoly.a
$(shell if [ ! -d lib ]; then mkdir lib; fi)
$(shell if [ ! -d release ]; then mkdir release; fi)
$(shell if [ ! -d debug ]; then mkdir debug; fi)

IFLAGS = -I/usr/local/include -Iinclude

CFLAGS_REL = -Wall -Ofast -D_THREAD_SAFE -pipe -msse2 -mssse3 -m32 -fno-exceptions -std=c++1z -stdlib=libc++
CFLAGS_DBG = -Wall -D_THREAD_SAFE -pipe -msse2 -mssse3 -m32 -fno-exceptions -std=c++1z -stdlib=libc++ -g3 -O0 -ggdb -DNDEBUG

LIBS =

CPP_FILES := $(wildcard src/*.cpp)
OBJ_FILES_REL := $(addprefix release/,$(notdir $(CPP_FILES:.cpp=.o)))
OBJ_FILES_DBG := $(addprefix debug/,$(notdir $(CPP_FILES:.cpp=.o)))


default: $(RELBIN) $(DBGBIN)
release: $(RELBIN)
debug: $(DBGBIN)

$(RELBIN): $(OBJ_FILES_REL)
	ar cru $(RELBIN) $(OBJ_FILES_REL) $(LIBS)
	ranlib $(RELBIN)
	chmod 700 $(RELBIN)

$(DBGBIN): $(OBJ_FILES_DBG)
	ar cru $(DBGBIN) $(OBJ_FILES_DBG) $(LIBS)
	ranlib $(DBGBIN)
	chmod 700 $(DBGBIN)

release/%.o: src/%.cpp
	$(CXX) $(CFLAGS_REL) $(IFLAGS) -c $< -o $@

debug/%.o: src/%.cpp
	$(CXX) $(CFLAGS_DBG) $(IFLAGS) -c $< -o $@

clean:
	rm -f debug/*.o
	rm -f release/*.o
	rm -f $(RELBIN)
	rm -f $(DBGBIN)

dep:
	touch src/Depend
	$(CXX) $(CFLAGS_DBG) $(IFLAGS) -MM src/*.cpp > src/Depend