#!/bin/bash

BLUE=$(tput setaf 4)
RESET=$(tput sgr0)

rendu_dir="."

# Compile the program (all .c in current directory)
c_files=$(find "$rendu_dir" -maxdepth 1 -name "test.c" -type f)
if [ -z "$c_files" ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: No .c files found$(tput sgr 0)"
    exit 1
fi

echo "${BLUE}Compiling n_queens program...${RESET}"
gcc -Wall -Werror -Wextra -o n_queens_test $c_files
if [ $? -ne 0 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: Compilation error$(tput sgr 0)"
    exit 1
fi

# Test 1: n=2 (0 solutions)
echo "${BLUE}Testing n=2...${RESET}"
./n_queens_test 2 > output2.txt 2>/dev/null
lines=$(wc -l < output2.txt)
if [ "$lines" -ne 0 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: n=2 should have 0 solutions, got $lines$(tput sgr 0)"
    cat output2.txt
    rm -f n_queens_test output*.txt
    exit 1
fi

# Test 2: n=3 (0 solutions)
echo "${BLUE}Testing n=3...${RESET}"
./n_queens_test 3 > output3.txt 2>/dev/null
lines=$(wc -l < output3.txt)
if [ "$lines" -ne 0 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: n=3 should have 0 solutions, got $lines$(tput sgr 0)"
    cat output3.txt
    rm -f n_queens_test output*.txt
    exit 1
fi

# Test 3: n=4 (exactly 2 solutions + exact content)
echo "${BLUE}Testing n=4 (sub.txt example)...${RESET}"
./n_queens_test 4 > output4.txt 2>/dev/null
lines=$(wc -l < output4.txt)
if [ "$lines" -ne 2 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: n=4 should have exactly 2 solutions, got $lines$(tput sgr 0)"
    cat output4.txt
    rm -f n_queens_test output*.txt
    exit 1
fi

sort output4.txt > sorted4.txt
echo -e "1 3 0 2\n2 0 3 1" | sort > expected4.txt
if ! diff -q sorted4.txt expected4.txt >/dev/null; then
    echo "$(tput setaf 1)$(tput bold)FAIL: n=4 solutions don't match expected$(tput sgr 0)"
    echo "Expected:"
    cat expected4.txt
    echo "Got:"
    cat sorted4.txt
    rm -f n_queens_test output*.txt sorted4.txt expected4.txt
    exit 1
fi

# Test 4: n=8 (92 solutions)
echo "${BLUE}Testing n=8...${RESET}"
./n_queens_test 8 > output8.txt 2>/dev/null
lines=$(wc -l < output8.txt)
if [ "$lines" -ne 92 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: n=8 should have 92 solutions, got $lines$(tput sgr 0)"
    rm -f n_queens_test output*.txt sorted4.txt expected4.txt
    exit 1
fi

# Wrong number of arguments
echo "${BLUE}Testing wrong number of arguments...${RESET}"
./n_queens_test > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: Should fail with no arguments$(tput sgr 0)"
    rm -f n_queens_test output*.txt sorted4.txt expected4.txt
    exit 1
fi

./n_queens_test 4 5 > /dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "$(tput setaf 1)$(tput bold)FAIL: Should fail with too many arguments$(tput sgr 0)"
    rm -f n_queens_test output*.txt sorted4.txt expected4.txt
    exit 1
fi

rm -f n_queens_test output*.txt sorted4.txt expected4.txt
echo "$(tput setaf 2)$(tput bold)PASSED :tada:$(tput sgr 0)"
exit 0
