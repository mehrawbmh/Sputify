OUTPUT := sputify.out
CC        := g++
CFLAGS    := --std=c++20
SRCDIR    := src
HEADERDIR := headers
BUILDDIR  := build
BINDIR    := .
TARGET    := $(BINDIR)/$(OUTPUT)
SOURCES   := $(shell find $(SRCDIR) -type f -name *.c*)
HEDEARS   := $(shell find $(HEADERDIR) -type f -name *.h*)
OBJECTS   := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .o,$(basename $(SOURCES))))
DEPS      := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(addsuffix .d,$(basename $(SOURCES))))
INC       := -I include -I src

all: debug
debug: CFLAGS += -g
debug: $(TARGET)
release: $(TARGET)
release: CFLAGS += -O3

all: $(TARGET)

clean:
	rm -rf $(BUILDDIR)

$(TARGET): $(BINDIR) $(BUILDDIR) $(OBJECTS)
	@$(CC) $(OBJECTS) -o $(TARGET)

$(BUILDDIR) :
	mkdir $(BUILDDIR)

$(BINDIR):
	mkdir $(BINDIR)
	
$(BUILDDIR)/%.o: $(SRCDIR)/%.c*
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<
	@$(CC) $(CFLAGS) $(INC) -M $< -MT $@ > $(@:.o=.td)
	@cp $(@:.o=.td) $(@:.o=.d); 
	@sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	-e '/^$$/ d' -e 's/$$/ :/' < $(@:.o=.td) >> $(@:.o=.d); 
	@rm -f $(@:.o=.td)


-include $(DEPS)

.PHONY: clean all
