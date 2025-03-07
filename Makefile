SRCDIR=src

# Source files
MAIN=$(SRCDIR)/main.c
INPUT=$(SRCDIR)/Input/input.c
MANAGEMENT=$(SRCDIR)/Management/management.c
LIST=$(SRCDIR)/List/list.c
SRC_FILES=$(MAIN) $(INPUT) $(MANAGEMENT) $(LIST)
# Compiler and its flags
COMPILER=gcc
CFLAGS=-Wall -Wextra -Wpedantic
DEBUGF=-g  # Debug flag

# Executables for both Linux and Windows
WINEXE=app.exe
LINUXEXE=app

# Normal build for Windows
winbuild:
	$(COMPILER) $(CFLAGS) $(SRC_FILES) -o $(WINEXE)

# Debug build for Windows
windebug:
	$(COMPILER) $(CFLAGS) $(DEBUGF) $(SRC_FILES) -o $(WINEXE)

# Normal build for Linux
linuxbuild:
	$(COMPILER) $(CFLAGS) $(SRC_FILES) -o $(LINUXEXE)

# Debug build for Linux
linuxdebug:
	$(COMPILER) $(CFLAGS) $(DEBUGF) $(SRC_FILES) -o $(LINUXEXE)

# Clean Executables
clean:
	rm -f $(LINUXEXE) $(WINEXE)

