all: run_tests

build_tests: tests/temp_test.c tests/terminated_test.c tests/sb_test.c
	mkdir -p ./bin/
	gcc tests/temp_test.c 			-o bin/temp_test
	gcc tests/terminated_test.c		-o bin/terminated_test
	gcc tests/sb_test.c 			-o bin/sb_test

run_tests: build_tests
	./bin/temp_test
	./bin/terminated_test
	./bin/sb_test
	echo "TESTS PASSED"