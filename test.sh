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

assert 0 "a a"
assert 1 "abc def"
assert 0 "abc abc"
assert 0 "abc (abc)"

assert 1 "a a(abc)+"
assert 0 "aabc a(abc)+"
assert 0 "abcabc (abc)+"
assert 0 "abcabcabc (abc)+"

assert 1 "abcabc (abc)?"
assert 0 "abc (abc)?"

assert 0 "a a(abc)?"

assert 0 "abc (abc)*"
assert 0 "abcabc (abc)*"
assert 0 "a a(abc)*"

assert 0 "b a|b"
assert 0 "a a|b"
assert 1 "c a|b"

assert 0 "abc (abc)|(def)"
assert 0 "def (abc)|(def)"
assert 1 "de (abc)|(def)"
