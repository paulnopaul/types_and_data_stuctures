CC := gcc
CFLAGS := -g3 -Wall -Werror
SOURCEDIR := ./source
BUILDDIR := ./bin
MAINTARGET := app.exe
SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(patsubst $(SOURCEDIR)/%.o,$(BUILDDIR)/%.o,$(SOURCES:.c=.o))

$(BUILDDIR)/$(MAINTARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	rm -rf $(BUILDDIR)/*
