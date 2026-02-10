#!/bin/bash

BLUE=$(tput setaf 4)
YELLOW=$(tput setaf 3)
RED=$(tput setaf 1)
GREEN=$(tput setaf 2)
BOLD=$(tput bold)
RESET=$(tput sgr0)

expected_files="test.c powerset.h"
rendu_dir="."

fail() {
    echo "${RED}${BOLD}FAIL: $1${RESET}"
    [ -n "$2" ] && echo "$2"
    exit 1
}

cleanup() {
    rm -f powerset_test output*.txt temp.txt
}

# Check required files
for file in $expected_files; do
    [ -f "$rendu_dir/$file" ] || fail "Missing file $file"
done

# Compile
echo "${BLUE}Compiling powerset...${RESET}"
gcc -Wall -Wextra -Werror -o powerset_test "$rendu_dir/test.c" || fail "Compilation error"

# -------- Helper: validate output for a given target and set --------
# Usage: validate_output <target> <set_elements...> < output_file
validate_output() {
    local target="$1"
    shift

    local -a set=("$@")
    local line sum tok idx last_idx found any_line
    any_line=0

    while IFS= read -r line; do
        any_line=1

        # Empty line => empty subset => sum must be 0
        if [ -z "$line" ]; then
            if [ "$target" -ne 0 ]; then
                fail "Empty subset printed but target != 0 (target=$target)"
            fi
            continue
        fi

        sum=0
        last_idx=-1

        # parse tokens
        for tok in $line; do
            # find token index in original set
            idx=-1
            for i in "${!set[@]}"; do
                if [ "${set[$i]}" = "$tok" ]; then
                    idx=$i
                    break
                fi
            done

            [ "$idx" -ge 0 ] || fail "Printed number '$tok' is not in original set" "Line: '$line'"

            # must respect original order => indices strictly increasing
            if [ "$idx" -le "$last_idx" ]; then
                fail "Subset does not respect original order" "Line: '$line'"
            fi
            last_idx=$idx

            # sum
            sum=$((sum + tok))
        done

        [ "$sum" -eq "$target" ] || fail "Subset sum mismatch (got $sum, expected $target)" "Line: '$line'"
    done

    # For impossible target, valid behavior is "no output" (no lines)
    # For target 0, valid behavior is at least one empty line OR other subsets summing to 0.
    # So we do not force any_line here (each test decides).
    return 0
}

# ----------------------- TESTS -----------------------

# Test 1: subject example
echo "${BLUE}Test 1: subject example (3 1 0 2 4 5 3)...${RESET}"
./powerset_test 3 1 0 2 4 5 3 > output1.txt 2>/dev/null || fail "Program exited non-zero on valid input"
validate_output 3 1 0 2 4 5 3 < output1.txt

# Test 2: simple 5 1 2 3 4 5
echo "${BLUE}Test 2: simple (5 1 2 3 4 5)...${RESET}"
./powerset_test 5 1 2 3 4 5 > output2.txt 2>/dev/null || fail "Program exited non-zero on valid input"
# must output at least one solution
[ -s output2.txt ] || fail "Expected at least one subset for target 5 with set 1 2 3 4 5"
validate_output 5 1 2 3 4 5 < output2.txt

# Test 3: target 0 must include empty subset line (per subject hint)
echo "${BLUE}Test 3: target 0 includes empty subset (0 1 -1)...${RESET}"
./powerset_test 0 1 -1 > output3.txt 2>/dev/null || fail "Program exited non-zero on valid input"
# must contain at least one empty line
grep -q "^$" output3.txt || fail "Target 0 must print empty subset as empty line"
validate_output 0 1 -1 < output3.txt

# Test 4: impossible target should produce no output (common strict tester rule)
# (Subject does not explicitly require it, but many testers do.)
echo "${BLUE}Test 4: impossible target (100 1 2 3)...${RESET}"
./powerset_test 100 1 2 3 > output4.txt 2>/dev/null || fail "Program exited non-zero on valid input"
# If you want to allow printing nothing OR just nothing, keep this:
[ ! -s output4.txt ] || fail "Impossible target should produce no output" "$(cat output4.txt)"

# Test 5: negative numbers (1 -1 2) must allow -1 2
echo "${BLUE}Test 5: negatives (1 -1 2)...${RESET}"
./powerset_test 1 -1 2 > output5.txt 2>/dev/null || fail "Program exited non-zero on valid input"
validate_output 1 -1 2 < output5.txt
# ensure at least one solution exists
grep -q "^-1 2$" output5.txt || grep -q "^-1 2" output5.txt || {
    # it might print "-1 2" exactly; accept any valid output but ensure some subset sums to 1 exists:
    if ! awk '{s=0; for(i=1;i<=NF;i++) s+=$i; if (NF>0 && s==1) ok=1} END{exit(ok?0:1)}' output5.txt; then
        fail "Expected at least one subset summing to 1 (e.g., '-1 2')"
    fi
}

# Test 6: single element
echo "${BLUE}Test 6: single element (5 5)...${RESET}"
./powerset_test 5 5 > output6.txt 2>/dev/null || fail "Program exited non-zero on valid input"
# valid output must contain exactly "5"
grep -q "^5$" output6.txt || fail "Expected subset '5' for input: 5 5" "$(cat output6.txt)"
validate_output 5 5 < output6.txt

# Test 7: wrong number of args (strict tester behavior)
# If you want subject-pure behavior, you can remove this block.
echo "${BLUE}Test 7: wrong arguments...${RESET}"
./powerset_test > temp.txt 2>&1
[ $? -ne 0 ] || fail "Should fail with no arguments"

./powerset_test 5 > temp.txt 2>&1
[ $? -ne 0 ] || fail "Should fail with only target argument"

# Cleanup
cleanup
echo "${GREEN}${BOLD}PASSED :tada:${RESET}"
exit 0
