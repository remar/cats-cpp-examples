CXXFLAGS += -I../../cats-cpp/src `sdl2-config --cflags`

CatsExample: CatsExample.o ../../cats-cpp/src/libcats.a ../../cats-cpp/src/Cats.h
	g++ -o $@ $^ -L../../cats-cpp/src -lcats `sdl2-config --libs` -lSDL2_image

clean:
	@rm -f *.o CatsExample
