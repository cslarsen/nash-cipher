CXXFLAGS = -W -Wall -g
TARGETS = nash

all: $(TARGETS)

check: all
	./nash

clean:
	rm -f $(TARGETS)
