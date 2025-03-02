SRCDIR=src

# Source files
FUNCS=$(SRCDIR)/functions.c
MAIN=$(SRCDIR)/main.c

# Compiler and its flags
COMPILER=gcc
CFLAGS=-Wall -Wextra -Wpedantic
DEBUGF=-g  # Debug flag

# Executables for both Linux and Windows
WINEXE=app.exe
LINUXEXE=app

# Normal build for Windows
winbuild:
	$(COMPILER) $(CFLAGS) $(MAIN) $(FUNCS) -o $(WINEXE)

# Debug build for Windows
windebug:
	$(COMPILER) $(CFLAGS) $(DEBUGF) $(MAIN) $(FUNCS) -o $(WINEXE)

# Normal build for Linux
linuxbuild:
	$(COMPILER) $(CFLAGS) $(MAIN) $(FUNCS) -o $(LINUXEXE)

# Debug build for Linux
linuxdebug:
	$(COMPILER) $(CFLAGS) $(DEBUGF) $(MAIN) $(FUNCS) -o $(LINUXEXE)

# Clean Executables
clean:
	rm -f $(LINUXEXE) $(WINEXE)

