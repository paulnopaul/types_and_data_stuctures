CC := gcc
CFLAGS := -g3 -Wall -Werror

SOURCEDIR := .
BUILDDIR := ../bin
MAINTARGET := app
CACHEDIR := ../cache

SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(patsubst $(SOURCEDIR)/%.o,$(BUILDDIR)/%.o,$(SOURCES:.c=.o))

$(BUILDDIR)/$(MAINTARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -f $(BUILDDIR)/*.o $(BUILDDIR)/$(MAINTARGET)
