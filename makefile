CXX=g++
CXXFLAGS=-Isrc -Wall -O3 -c
OBJDIR=lib
OBJ=$(OBJDIR)/main.o $(OBJDIR)/bytebuffer.o
EXE=Bytebuffer

.PHONY: all clean

all: $(EXE)

Bytebuffer: $(OBJ)
	$(CXX) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CXX) $(CXXFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(EXE)
