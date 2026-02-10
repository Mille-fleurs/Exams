#!/bin/bash
set -u

BLUE=$(tput setaf 4)
GREEN=$(tput setaf 2)
RED=$(tput setaf 1)
BOLD=$(tput bold)
RESET=$(tput sgr0)

SRC="test.c"
BIN="./permutations_test"

fail() {
  echo "${RED}${BOLD}FAIL: $1${RESET}"
  exit 1
}

pass() {
  echo "${GREEN}${BOLD}PASSED :tada:${RESET}"
  exit 0
}

# --- Sanity checks ---
[ -f "$SRC" ] || fail "Missing $SRC"
[ -f "permutations.h" ] || fail "Missing permutations.h"

# --- Best-effort forbidden function scan (not perfect, but helpful) ---
# Allowed: puts, malloc, calloc, realloc, free, write
# Disallowed common: printf, dprintf, puts is allowed, strlen, strcmp, qsort, etc.
echo "${BLUE}Scanning for common forbidden functions (best-effort)...${RESET}"
if grep -nE '\b(printf|dprintf|fprintf|sprintf|snprintf|strlen|strcmp|strncmp|strcpy|strncpy|strcat|strncat|qsort|system|exec|fork|popen|getline)\b' "$SRC" >/dev/null 2>&1; then
  echo "${RED}${BOLD}WARNING:${RESET} Found suspicious libc calls in $SRC:"
  grep -nE '\b(printf|dprintf|fprintf|sprintf|snprintf|strlen|strcmp|strncmp|strcpy|strncpy|strcat|strncat|qsort|system|exec|fork|popen|getline)\b' "$SRC" || true
  echo "If this is Exam03, using forbidden functions will fail even if output is correct."
fi

# --- Compile (show errors) ---
echo "${BLUE}Compiling...${RESET}"
gcc -Wall -Wextra -Werror -o "$BIN" "$SRC" || fail "Compilation error"

# Helper: run and capture output (stdout only)
run_case() {
  local input="$1"
  local out="$2"
  "$BIN" "$input" > "$out"
}

# Helper: assert exact output match
assert_exact() {
  local out="$1"
  local expected="$2"
  local got
  got="$(cat "$out")"
  if [ "$got" != "$expected" ]; then
    echo "${RED}${BOLD}FAIL:${RESET} Output mismatch"
    echo "Input: $3"
    echo "Expected:"
    printf "%s\n" "$expected"
    echo "Got:"
    cat "$out"
    fail "Wrong output"
  fi
}

# Helper: check each line formatting (no spaces, correct length)
check_lines_format() {
  local out="$1"
  local n="$2"   # expected length per line
  while IFS= read -r line; do
    # ignore possible empty final line due to trailing newline in some tools
    [ -z "$line" ] && continue
    echo "$line" | grep -qE '^[^[:space:]]+$' || fail "Line contains whitespace: '$line'"
    [ "${#line}" -eq "$n" ] || fail "Wrong line length (${#line} != $n): '$line'"
  done < "$out"
}

# Helper: check lexicographic order (strict)
check_sorted() {
  local out="$1"
  if ! LC_ALL=C sort "$out" | diff -q - "$out" >/dev/null; then
    fail "Output is not in lexicographic order"
  fi
}

# Helper: check uniqueness
check_unique() {
  local out="$1"
  local total uniq
  total=$(wc -l < "$out")
  uniq=$(LC_ALL=C sort "$out" | uniq | wc -l)
  [ "$total" -eq "$uniq" ] || fail "Duplicate lines found ($uniq unique out of $total)"
}

# Helper: factorial (small n)
fact() {
  local n="$1"
  local r=1
  local i=2
  while [ "$i" -le "$n" ]; do
    r=$((r * i))
    i=$((i + 1))
  done
  echo "$r"
}

# --- Required tests (subject examples) ---
echo "${BLUE}Test: a${RESET}"
run_case "a" out_a.txt
assert_exact out_a.txt "a" "a"
check_lines_format out_a.txt 1

echo "${BLUE}Test: ab${RESET}"
run_case "ab" out_ab.txt
assert_exact out_ab.txt $'ab\nba' "ab"
check_lines_format out_ab.txt 2
check_sorted out_ab.txt
check_unique out_ab.txt

echo "${BLUE}Test: abc${RESET}"
run_case "abc" out_abc.txt
assert_exact out_abc.txt $'abc\nacb\nbac\nbca\ncab\ncba' "abc"
check_lines_format out_abc.txt 3
check_sorted out_abc.txt
check_unique out_abc.txt

# --- Extra strict tests (still reasonable) ---
echo "${BLUE}Test: bac (should still output permutations in sorted order)${RESET}"
run_case "bac" out_bac.txt
assert_exact out_bac.txt $'abc\nacb\nbac\nbca\ncab\ncba' "bac"

echo "${BLUE}Test: abcd (count/order/format/unique)${RESET}"
run_case "abcd" out_abcd.txt
lines=$(wc -l < out_abcd.txt)
expected=$(fact 4)
[ "$lines" -eq "$expected" ] || fail "'abcd' should have $expected lines, got $lines"
check_lines_format out_abcd.txt 4
check_sorted out_abcd.txt
check_unique out_abcd.txt

# --- Cleanup ---
rm -f "$BIN" out_*.txt

pass