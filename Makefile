CXX = g++-9
CC = gcc-9
PROGRAM1 = files
PROGRAM2 = cfiles
CXXFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu++17 -O0 `pkg-config --cflags glib-2.0`
CFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu11 -O0 `pkg-config --cflags glib-2.0`
LDLIBS = `pkg-config --libs glib-2.0`

default: bin/$(PROGRAM1) bin/$(PROGRAM2)

bin/$(PROGRAM1): bin/$(PROGRAM1).o
	$(CXX) $^ $(LDLIBS) -o $@

bin/$(PROGRAM2): bin/$(PROGRAM2).o
	$(CC) $^ $(LDLIBS) -o $@

bin/$(PROGRAM1).o: src/$(PROGRAM1).cc
	$(CXX) $(CXXFLAGS) -o $@ -c $<

bin/$(PROGRAM2).o: src/$(PROGRAM2).c
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fv bin/*.o bin/$(PROGRAM1) bin/$(PROGRAM2)
