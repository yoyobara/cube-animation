APP_NAME = cube_animation

SOURCES = $(shell find -name "*.c")
INCLUDE_DIR = include

CFLAGS = $(shell pkg-config --cflags sdl2)
LIBS = $(shell pkg-config --libs sdl2)

$(APP_NAME): $(SOURCES)
	$(CC) -I $(INCLUDE_DIR) $(CFLAGS) -o $(APP_NAME) $(SOURCES) $(LIBS)

.PHONY: clean
clean:
	rm $(APP_NAME)
