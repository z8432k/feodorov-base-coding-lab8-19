CC = g++-9
PROGRAM = files
CFLAGS = -Wall -Wextra -Wpedantic -ggdb -std=gnu++17 -O0 `pkg-config --cflags glib-2.0`
LDLIBS = `pkg-config --libs glib-2.0`

default: bin/$(PROGRAM)

bin/$(PROGRAM): bin/$(PROGRAM).o
	$(CC) $^ $(LDLIBS) -o $@

bin/$(PROGRAM).o: src/$(PROGRAM).cc
	$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm -fv bin/*.o bin/$(PROGRAM)
