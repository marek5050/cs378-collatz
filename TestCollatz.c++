/** \file TestCollatz.c++
 *   Test harness for Collatz
 *  By. Marek5050
 */


// https://code.google.com/p/googletest/wiki/V1_7_Primer#Basic_Assertions

// --------
// includes
// --------

#include <iostream> // cout, endl
#include <sstream>  // istringtstream, ostringstream
#include <string>   // string
#include <utility>  // pair

#include "gtest/gtest.h"

#include "Collatz.h"

using namespace std;

// -----------
// TestCollatz
// -----------

// ----
// read
// ----

TEST(Collatz, read_1) {
    string s("1 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ( 1, p.first);
    ASSERT_EQ(10, p.second);}

TEST(Collatz, read_2) {
    string s("10 1\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(10, p.first);
    ASSERT_EQ( 1, p.second);}


TEST(Collatz, read_3) {
    string s("10 10\n");
    const pair<int, int> p = collatz_read(s);
    ASSERT_EQ(10, p.first);
    ASSERT_EQ(10, p.second);}


// ----
// eval
// ----

TEST(Collatz, eval_1) {
    const int v = collatz_eval(1, 10);
    ASSERT_EQ(20, v);}

TEST(Collatz, eval_2) {
    const int v = collatz_eval(100, 200);
    ASSERT_EQ(125, v);}

TEST(Collatz, eval_3) {
    const int v = collatz_eval(201, 210);
    ASSERT_EQ(89, v);}

TEST(Collatz, eval_4) {
    const int v = collatz_eval(900, 1000);
    ASSERT_EQ(174, v);}

TEST(Collatz, eval_5) {
    const int v = collatz_eval(1,1);
    ASSERT_EQ(1, v);}

TEST(Collatz, eval_6) {
    const int v = collatz_eval(1, 2);
    ASSERT_EQ(2, v);}

TEST(Collatz, eval_7) {
    const int v = collatz_eval(3,1);
    ASSERT_EQ(8, v);}

TEST(Collatz, eval_8) {
    const int v = collatz_eval(1,999999);
    ASSERT_EQ(525, v);}

TEST(Collatz, eval_9) {
    const int v = collatz_eval(3248,61);
    ASSERT_EQ(217, v);}


// -----
// print
// -----

TEST(Collatz, print_1) {
    ostringstream w;
    collatz_print(w, 1, 10, 20);
    ASSERT_EQ("1 10 20\n", w.str());}

TEST(Collatz, print_2) {
    ostringstream w;
    collatz_print(w, 10, 1, 20);
    ASSERT_EQ("10 1 20\n", w.str());}

TEST(Collatz, print_3) {
    ostringstream w;
    collatz_print(w, 1, 1, 1);
    ASSERT_EQ("1 1 1\n", w.str());}
// -----
// solve
// -----

TEST(Collatz, solve_1) {
    istringstream r("1 10\n100 200\n201 210\n900 1000\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 10 20\n100 200 125\n201 210 89\n900 1000 174\n", w.str());}


/**
74 811 171
54 521 144
67 661 145
57 801 171
38 471 144
*/

TEST(Collatz, solve_2) {
    istringstream r("74 811\n54 521\n67 661\n57 801\n38 471\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("74 811 171\n54 521 144\n67 661 145\n57 801 171\n38 471 144\n", w.str());}

/**
16 761 171
3 241 128
25 641 144
40 311 128
20 541 144
56 31 113
42 451 144
*/

TEST(Collatz, solve_3) {
    istringstream r("16 761\n3 241\n25 641\n40 311\n20 541\n56 31\n42 451\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("16 761 171\n3 241 128\n25 641 144\n40 311 128\n20 541 144\n56 31 113\n42 451 144\n", w.str());}

TEST(Collatz, solve_4) {
    istringstream r("1 999999\n14140 23675\n597034 602378\n134 3007\n");
    ostringstream w;
    collatz_solve(r, w);
    ASSERT_EQ("1 999999 525\n14140 23675 282\n597034 602378 403\n134 3007 217\n", w.str());}



TEST(Collatz, collatz_cache){
    collatz_cache();
}

/*
% ls -al /usr/include/gtest/
...
gtest.h
...



% locate libgtest.a
/usr/lib/libgtest.a
...



% locate libpthread.a
...
/usr/lib32/libpthread.a



% locate libgtest_main.a
/usr/lib/libgtest_main.a
...



% g++-4.7 -fprofile-arcs -ftest-coverage -pedantic -std=c++11 -Wall Collatz.c++ TestCollatz.c++ -o TestCollatz -lgtest -lgtest_main -lpthread



% valgrind TestCollatz        >  TestCollatz.out 2>&1
% gcov-4.7 -b Collatz.c++     >> TestCollatz.out
% gcov-4.7 -b TestCollatz.c++ >> TestCollatz.out



% cat TestCollatz.out
==14225== Memcheck, a memory error detector
==14225== Copyright (C) 2002-2011, and GNU GPL'd, by Julian Seward et al.
==14225== Using Valgrind-3.7.0 and LibVEX; rerun with -h for copyright info
==14225== Command: TestCollatz
==14225==
Running main() from gtest_main.cc
[==========] Running 7 tests from 1 test case.
[----------] Global test environment set-up.
[----------] 7 tests from Collatz
[ RUN      ] Collatz.read
[       OK ] Collatz.read (31 ms)
[ RUN      ] Collatz.eval_1
[       OK ] Collatz.eval_1 (5 ms)
[ RUN      ] Collatz.eval_2
[       OK ] Collatz.eval_2 (3 ms)
[ RUN      ] Collatz.eval_3
[       OK ] Collatz.eval_3 (3 ms)
[ RUN      ] Collatz.eval_4
[       OK ] Collatz.eval_4 (3 ms)
[ RUN      ] Collatz.print
[       OK ] Collatz.print (17 ms)
[ RUN      ] Collatz.solve
[       OK ] Collatz.solve (10 ms)
[----------] 7 tests from Collatz (88 ms total)

[----------] Global test environment tear-down
[==========] 7 tests from 1 test case ran. (132 ms total)
[  PASSED  ] 7 tests.
==14225==
==14225== HEAP SUMMARY:
==14225==     in use at exit: 0 bytes in 0 blocks
==14225==   total heap usage: 495 allocs, 495 frees, 70,302 bytes allocated
==14225==
==14225== All heap blocks were freed -- no leaks are possible
==14225==
==14225== For counts of detected and suppressed errors, rerun with: -v
==14225== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)
File 'Collatz.c++'
Lines executed:100.00% of 17
Branches executed:100.00% of 18
Taken at least once:61.11% of 18
Calls executed:89.47% of 19
Creating 'Collatz.c++.gcov'
...
File 'TestCollatz.c++'
Lines executed:100.00% of 26
Branches executed:57.14% of 224
Taken at least once:28.57% of 224
Calls executed:54.07% of 209
Creating 'TestCollatz.c++.gcov'
...
*/
