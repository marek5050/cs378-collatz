FILES :=                              \
    .travis.yml                       \
    Collatz.c++                       \
    Collatz.h                         \
    Collatz.log                       \
    html                              \
    RunCollatz.c++                    \
    RunCollatz.in                     \
    RunCollatz.out                    \
    TestCollatz.c++                   \
    TestCollatz.out

ifeq ($(CXX), clang++)
    COVFLAGS := --coverage
    GCOV     := gcov
else
    CXX      := g++
    COVFLAGS := -fprofile-arcs -ftest-coverage
    GCOV     := gcov
endif

CXXFLAGS := -pedantic -Wall
LDFLAGS  := -lgtest -lgtest_main -pthread
VALGRIND := valgrind

all: RunCollatz TestCollatz

check:
	@for i in $(FILES);                                         \
	do                                                          \
        [ -e $$i ] && echo "$$i found" || echo "$$i NOT FOUND"; \
    done

clean:
	rm -f *.gcda
	rm -f *.gcno
	rm -f *.gcov
	rm -f RunCollatz
	rm -f TestCollatz

config:
	git config -l

test: RunCollatz.out TestCollatz.out

collatz-tests:
	git clone https://github.com/cs378-summer-2015/collatz-tests.git

html: Doxyfile Collatz.h Collatz.c++ RunCollatz.c++ TestCollatz.c++
	doxygen Doxyfile

Collatz.log:
	git log > Collatz.log

Doxyfile:
	doxygen -g

RunCollatz: Collatz.h Collatz.c++ RunCollatz.c++
	$(CXX) $(CXXFLAGS) Collatz.c++ RunCollatz.c++ -o RunCollatz

RunCollatz.out: RunCollatz
	cat RunCollatz.in
	./RunCollatz < RunCollatz.in > RunCollatz.out
	cat RunCollatz.out

TestCollatz: Collatz.h Collatz.c++ TestCollatz.c++
	$(CXX) $(COVFLAGS) $(CXXFLAGS) Collatz.c++ TestCollatz.c++ -o TestCollatz $(LDFLAGS)

TestCollatz.out: TestCollatz
	-$(VALGRIND) ./TestCollatz  >  TestCollatz.out 2>&1
	$(GCOV) -r -b Collatz.c++     >> TestCollatz.out
	$(GCOV) -r -b TestCollatz.c++ >> TestCollatz.out
	cat TestCollatz.out
