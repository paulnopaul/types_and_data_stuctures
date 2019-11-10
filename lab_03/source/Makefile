BUILDDIR := ../bin
SOURCEDIR := .
MAINTARGET := app.exe
CC := gcc
CFLAGS := -std=c99 -Wall -Werror -g3
SOURCES := $(wildcard $(SOURCEDIR)/*.c)
OBJECTS := $(patsubst $(SOURCEDIR)/%.o, $(BUILDDIR)/%.o, $(SOURCES:.c=.o))

$(BUILDDIR)/$(MAINTARGET): $(OBJECTS)
	$(CC) -o $@ $^

$(BUILDDIR)/%.o: $(SOURCEDIR)/%.c
	$(CC) $< $(CFLAGS) -c -o $@

clean:
	-rm $(BUILDDIR)/$(MAINTARGET) $(OBJECTS)
