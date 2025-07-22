all: run_tests

build_tests: tests/append_test.c tests/concat_test.c tests/copy_test.c tests/free_test.c tests/pop_test.c tests/reverse_test.c
	mkdir -p ./bin/
	gcc tests/append_test.c 	-o bin/append_test
	gcc tests/concat_test.c 	-o bin/concat_test
	gcc tests/copy_test.c 		-o bin/copy_test
	gcc tests/free_test.c 		-o bin/free_test
	gcc tests/pop_test.c 		-o bin/pop_test
	gcc tests/reverse_test.c 	-o bin/reverse_test

run_tests: build_tests
	./bin/append_test
	./bin/concat_test
	./bin/copy_test
	./bin/free_test
	./bin/pop_test
	./bin/reverse_test
	echo "TESTS PASSED"