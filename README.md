# simple-re-compiler

### CAUTION: The code is at very early stage, so it may not work properly.

This is a simple (and presumably very slow) compiler of regular expressions. It supports minimal numbers of regex operators: ```?, *, +, |```.

## Usage
1. ```make```
2. ```./comp "input string" "regex"``` (ex: ```./comp "abcabcabc" "(abc)*"```)

## references
The transformation from the regex to the nondeterministic finite automata with ε-moves is based on the Thompson algorithm, the details of which are clearly explained in [this article](https://swtch.com/~rsc/regexp/regexp1.html) by Russ Cox.

The implementation of the parser and tokenizer mimics the one used in the early version of [chibicc](https://github.com/rui314/chibicc) by Rui Ueyama.
