CC ?= gcc
CFLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -O2
SAN_FLAGS := -std=c11 -Wall -Wextra -Wpedantic -Werror -g -O1 -fsanitize=address,undefined
LDFLAGS := -lm

BUILD_DIR := build
APP_BIN := $(BUILD_DIR)/ordenacao_precos
TEST_BIN := $(BUILD_DIR)/test_ordenacao
SAN_TEST_BIN := $(BUILD_DIR)/test_ordenacao_san

.PHONY: all run test sanitize clean

all: $(APP_BIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(APP_BIN): src/main.c src/ordenacao.c src/ordenacao.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) src/main.c src/ordenacao.c -o $@

$(TEST_BIN): tests/test_ordenacao.c src/ordenacao.c src/ordenacao.h | $(BUILD_DIR)
	$(CC) $(CFLAGS) tests/test_ordenacao.c src/ordenacao.c -o $@ $(LDFLAGS)

$(SAN_TEST_BIN): tests/test_ordenacao.c src/ordenacao.c src/ordenacao.h | $(BUILD_DIR)
	$(CC) $(SAN_FLAGS) tests/test_ordenacao.c src/ordenacao.c -o $@ $(LDFLAGS)

run: $(APP_BIN)
	./$(APP_BIN)

test: $(APP_BIN) $(TEST_BIN)
	./$(TEST_BIN)
	bash tests/test_cli.sh ./$(APP_BIN)

sanitize: $(SAN_TEST_BIN)
	./$(SAN_TEST_BIN)

clean:
	rm -rf $(BUILD_DIR)
