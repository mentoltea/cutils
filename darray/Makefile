all: run_tests

build_tests: tests/free_test.c tests/append_test.c tests/concat_test.c
	mkdir -p ./bin/
	gcc tests/free_test.c -o bin/free_test
	gcc tests/append_test.c -o bin/append_test
	gcc tests/concat_test.c -o bin/concat_test

run_tests: build_tests
	./bin/free_test
	./bin/append_test
	./bin/concat_test