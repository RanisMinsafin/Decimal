NAME = Project
CC = gcc -g -Wall -Werror -Wextra -std=c11
GCOVFLAGS = -fprofile-arcs -ftest-coverage
SOURSES = s21_*.c
OBJECT = $(patsubst %*.c, %*.o,  ${SOURSES})
OS := $(shell uname -s)

ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lcheck
endif
ifeq ($(OS), Linux)
 CC += -D OS_LINUX
 ADD_LIB = -lcheck -lm -lrt -lpthread
 TEST_FLAGS =-lpthread -lcheck -pthread -lrt -lm
endif
ifeq ($(OS), Darwin)
 CC += -D OS_MAC
 ADD_LIB =
 TEST_FLAGS =-lcheck
endif

all: clean s21_decimal.a

$(NAME): $(OBJECT)
	$(CC) $(OBJECT) -o $(NAME)

s21_decimal.a:$(SOURSES)
	$(CC) -c -lcheck $(SOURSES)
	@ar rcs s21_decimal.a $(OBJECT)

test: test.c
# test: decimal_test.c
	$(CC) $< s21_decimal.a $(TEST_FLAGS) -o unit-test

gcov_report: s21_decimal.a
	@gcc $(GCOVFLAGS) test.c -lcheck $(SOURSES) $(TEST_FLAGS) -o GcovReport
	@./GcovReport
	@lcov -t "GcovReport" -o GcovReport.info -c -d .
	@genhtml -o report GcovReport.info
	@open ./report/index-sort-f.html
	@rm -rf ./*.gcno ./*.gcda ./GcovReport.*

clean:
	@rm -rf ./*.o ./*.a ./a.out ./GcovReport ./*.gcno ./*.gcda ./report ./*.info ./decimal_o ./*.dSYM ./unit-test ./CPPLINT*
clean2:
	@rm -r ./*.o

lo:
	for i in `seq 100 $(OP)`;	do ./unit-test; done;

valgrind_check: s21_decimal.a
	CK_FORK=no valgrind --tool=memcheck ./unit-test

lik: s21_decimal.a
	CK_FORK=no leaks -atExit -- ./unit-test

rebuild:
	$(MAKE) clean
	$(MAKE) all
