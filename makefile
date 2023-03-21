CXX=g++
CXXFLAGS=-Isrc -Wall -O3 -c
LXXFLAGS= -Llib -lbytebuffer
OBJDIR=obj
LIBDIR=lib
OBJ=$(OBJDIR)/main.o $(OBJDIR)/bytebuffer.o
LIB=$(LIBDIR)/libbytebuffer.a
EXE=Bytebuffer

.PHONY: all target clean

all: $(EXE)

Bytebuffer: $(LIB) $(OBJ)
	$(CXX) $(OBJDIR)/main.o $(LXXFLAGS) -o $@

target: $(LIB)

$(LIBDIR)/%.a: $(OBJ) | $(LIBDIR)
	ar rvs $@ $(OBJDIR)/bytebuffer.o

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

$(LIBDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(LIBDIR) $(EXE)
