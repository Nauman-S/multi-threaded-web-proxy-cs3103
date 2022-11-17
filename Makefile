CC = gcc #clang
CXX = g++ #clang++
CFLAGS := $(CFLAGS) -g -O3 -Wall -Wextra -pedantic -pthread -Werror -std=c18
CXXFLAGS := $(CXXFLAGS) -g -O3 -Wall -Wextra -pedantic -pthread -Werror -std=c++14

all: proxy

SRCS = main.cpp Proxy.cpp HttpRequest.cpp HttpResponse.cpp TcpConnection.cpp ImageSubstitution.cpp

proxy: $(SRCS:%=%.o)
	$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@

.PHONY: clean
clean:
	rm -f *.o proxy

# dependency handling
# https://make.mad-scientist.net/papers/advanced-auto-dependency-generation/#tldr

DEPDIR := .deps
DEPFLAGS = -MT $@ -MMD -MP -MF $(DEPDIR)/$<.d

COMPILE.c = $(CC) $(DEPFLAGS) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c
COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.c.o: %.c
%.c.o: %.c $(DEPDIR)/%.c.d | $(DEPDIR)
	$(COMPILE.c) $(OUTPUT_OPTION) $<

%.cpp.o: %.cpp
%.cpp.o: %.cpp $(DEPDIR)/%.cpp.d | $(DEPDIR)
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<

$(DEPDIR): ; @mkdir -p $@

DEPFILES := $(SRCS:%=$(DEPDIR)/%.d) $(DEPDIR)/client.c.d
$(DEPFILES):

include $(wildcard $(DEPFILES))
