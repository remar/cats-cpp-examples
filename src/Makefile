CXXFLAGS += -I../../cats-cpp/src

CatsExample: CatsExample.o
	g++ -o $@ $^ -L../../cats-cpp/src -lcats `sdl2-config --libs`

clean:
	@rm *.o CatsExample
