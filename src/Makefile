CXXFLAGS += -I../../cats-cpp/src `sdl2-config --cflags`

CatsExample: CatsExample.o
	g++ -o $@ $^ -L../../cats-cpp/src -lcats `sdl2-config --libs`

clean:
	@rm -f *.o CatsExample
