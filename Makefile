CXX = clang++
SDL_LIB = -L/usr/local/lib -lSDL2
GL_LIB = -lGL -lGLEW
EXE = terrain
CFLAGS = -std=c++11
LDFLAGS = $(SDL_LIB) $(GL_LIB)

all: $(EXE)

$(EXE): main.o window.o shader.o mesh.o
	$(CXX) $(LDFLAGS) $^ -o $@

.cpp.o:
	$(CXX) $(CFLAGS) -c $< -o $@

clean:
	rm *.o && rm $(EXE)
