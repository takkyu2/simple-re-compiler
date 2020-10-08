# simple-re-compiler

### CAUTION: The code is at very early stage, so it may not work properly.

This is a simple compiler of regular expressions. It supports minimal numbers of operators: ```?, *, +, |```.

## references
The transformation from regex to the nondeterministic finite automata with ε-moves is based on the Thompson algorithm, of which details are clearly explained in [this article](https://swtch.com/~rsc/regexp/regexp1.html) by Russ Cox.

The implementation of the parser and tokenizer mimics the one of [chibicc](https://github.com/rui314/chibicc) by Rui Ueyama.