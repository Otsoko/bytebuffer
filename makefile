CXX=g++
AR=ar
RL=ranlib
CP=cp -r

#CXXFLAGS=-Isrc -Ilib -Wall -Wextra -O3 -c
CXXFLAGS=-Isrc -Ilib -Wall -Wextra -g -c
LXXFLAGS= -Llib -lbbuffer

OBJDIR=obj
LIBDIR=lib
SRCDIR=src

OBJ=$(OBJDIR)/main.o $(OBJDIR)/bbuffer.o
LIB=$(LIBDIR)/libbbuffer.a
EXE=bbuffer

.PHONY: all target clean

all: $(EXE)

bbuffer: $(LIB) $(OBJ)
	$(CXX) $(OBJDIR)/main.o $(LXXFLAGS) -o $@

target: $(LIB)

$(LIBDIR)/%.a: $(OBJ) | $(LIBDIR)
	$(AR) rf $@ $(OBJDIR)/bbuffer.o
	$(RL) $@
	$(CP) -f $(SRCDIR)/bbuffer.h $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(LIBDIR) $(EXE)
