FILES = GameRunner.cpp Game.cpp Game.h
TEST_FILES = Game.cpp Game.h
CC = g++
OPTS = -std=c++17 -Wall -Wextra -Werror
OUTOPTS = -o 
OUT = out/trivia
TEST_OUT = out/trivia_tests

.PHONY:  .outputFolder all prod tests runTest clean

all: prod 

prod: run

tests: runTest

.outputFolder:
	mkdir -p out

$(OUT): .outputFolder $(FILES)
	$(CC) $(FILES) $(OPTS) $(OUTOPTS) $(OUT)

run: $(OUT)
	./$(OUT)

$(TEST_OUT): .outputFolder 
	$(CC) $(TEST_FILES) $(OPTS) $(OUTOPTS) $(TEST_OUT)

runTest: $(TEST_OUT)
	./$(TEST_OUT)

clean: 
	rm -rf out/
