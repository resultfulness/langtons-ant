PROJECT = langtons-ant

CC     = cc
CFLAGS = -std=c99 -pedantic -Wall
LDLIBS =
SRCDIR   = ./src
BUILDDIR = ./build
OUTDIR   = ./out

OBJECTS = $(patsubst %.c,%.o,$(shell find $(SRCDIR) -type f -name '*.c'))

all: $(PROJECT)

$(PROJECT): dir $(OBJECTS)
	$(CC) $(CFLAGS) $(LDLIBS) -o $@ $(patsubst %,build/%,$(OBJECTS))

$(OBJECTS): dir
	@mkdir -p $(BUILDDIR)/$(@D)
	@$(CC) $(CFLAGS) -o $(BUILDDIR)/$@ -c $*.c

dir:
	@mkdir -p $(BUILDDIR)
	@mkdir -p $(OUTDIR)

clean:
	@rm -rf $(BUILDDIR) $(OUTDIR) $(PROJECT)

.PHONY: all clean dir

