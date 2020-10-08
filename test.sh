#!/bin/bash
assert() {
    expected="$1"
    input="$2"

    ./comp $input
    actual="$?"

    if [ "$actual" = "$expected" ]; then
        echo "$input => $actual"
    else
        echo "$input => $expected expected, but got $actual"
        exit 1
    fi
}

assert 1 "a a"
assert 0 "abc def"
assert 1 "abc abc"
assert 1 "abc (abc)"

assert 0 "a a(abc)+"
assert 1 "aabc a(abc)+"
assert 1 "abcabc (abc)+"
assert 1 "abcabcabc (abc)+"

assert 0 "abcabc (abc)?"
assert 1 "abc (abc)?"

assert 1 "a a(abc)?"

assert 1 "abc (abc)*"
assert 1 "abcabc (abc)*"
assert 1 "a a(abc)*"

assert 1 "b a|b"
assert 1 "a a|b"
assert 0 "c a|b"

assert 1 "abc (abc)|(def)"
assert 1 "def (abc)|(def)"
assert 0 "de (abc)|(def)"
