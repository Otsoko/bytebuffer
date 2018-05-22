CC=g++
CFLAGS=-Isrc -Wall -O3 -c
OBJDIR=lib
OBJ=$(OBJDIR)/main.o $(OBJDIR)/bytebuffer.o
EXE=Bytebuffer

.PHONY: all clean

all: $(EXE)

Bytebuffer: $(OBJ)
	$(CC) -o $@ $^

$(OBJDIR)/%.o: src/%.cpp | $(OBJDIR)
	$(CC) $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $@

clean:
	rm -rf $(OBJDIR) $(EXE)
