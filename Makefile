APP_NAME = exers
SOURCES = $(shell find -name "*.c")
INCLUDE_DIR = include

$(APP_NAME): $(SOURCES)
	$(CC) -I $(INCLUDE_DIR) -o $(APP_NAME) $(SOURCES)

.PHONY: clean
clean:
	rm $(APP_NAME)
