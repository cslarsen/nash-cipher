CXXFLAGS = -W -Wall -g
TARGETS = nash

all: $(TARGETS)

run: nash
	./nash

clean:
	rm -f $(TARGETS)
