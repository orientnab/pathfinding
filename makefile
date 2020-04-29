.ONESHELL:
.DELETE_ON_ERROR:
MAKEFLAGS += --warn-undefined-variables
MAKEFLAGS += --no-builtin-rules

# Project name
EXE = pathFinding

# Project files
SRCDIR = ./src

SRCS = main.cpp \
			 algo_dijkstra.cpp \
			 read_flags.cpp \
			 read_map.cpp

OBJS = $(SRCS:.cpp=.o)

# Tests
TESTSRCS = readAsciiMap.cpp \
					 readFlags.cpp

# Compiler
CC     = g++
CFLAGS = -std=c++17 -Wall -Werror -Wextra
LFLAGS = -L/usr/include/boost
LFLAGS += -lboost_program_options
TFLAGS = -lgtest

# Debug build settings
DBGDIR = debug
DBGEXE = $(DBGDIR)/$(EXE)
DBGOBJS = $(addprefix $(DBGDIR)/, $(OBJS))
DBGCFLAGS = -g -O0 -DDEBUG

# Release build settings
RELDIR = release
RELEXE = $(RELDIR)/$(EXE)
RELOBJS = $(addprefix $(RELDIR)/, $(OBJS))
RELCFLAGS = -O3 -DNDEBUG

# Test settings
TESTDIR = test
TESTOBJSSRC = $(addprefix $(TESTDIR)/, $(filter-out main.o, $(OBJS)))
TESTOBJS = $(addprefix $(TESTDIR)/, $(TESTSRCS:.cpp=.o))
TESTEXE = $(addprefix $(TESTDIR)/, $(TESTSRCS:.cpp=))

.PHONY: all clean debug prep release remake test

all: prep release

# Debug rules
debug: $(DBGEXE)

$(DBGEXE): $(DBGOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(DBGCFLAGS) -o $(DBGEXE) $^

$(DBGDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(DBGCFLAGS) -o $@ $<

# Release rules
release: $(RELEXE)

$(RELEXE): $(RELOBJS)
	$(CC) $(CFLAGS) $(LFLAGS) $(RELCFLAGS) -o $(RELEXE) $^

$(RELDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

# Test rules
test: $(TESTEXE) runtests

runtests: $(TESTEXE)
	@for test in $^ ; do \
		$${test}; \
	done

$(TESTEXE): $(TESTOBJS) $(TESTOBJSSRC)
	$(CC) $(CFLAGS) $(LFLAGS) $(TFLAGS) $(RELCFLAGS) \
		-o $@ $(patsubst %,%.o, $@) $(TESTOBJSSRC)

$(TESTDIR)/%.o: $(SRCDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<
$(TESTDIR)/%.o: $(TESTDIR)/%.cpp
	$(CC) -c $(CFLAGS) $(RELCFLAGS) -o $@ $<

# Tools
prep:
	@mkdir -p $(DBGDIR) $(RELDIR) $(TESTDIR)

remake: clean all

clean:
	rm -f $(RELEXE) $(RELOBJS) $(DBGEXE) $(DBGOBJS)

