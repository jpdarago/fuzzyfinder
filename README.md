fuzzymatcher
============

Fuzzy select among lines in stdout.

It tries to imitate selecta (https://github.com/garybernhardt/selecta)
but it is written in C so it should be faster (I haven't profiled so I
might be wrong) but it lacks some features (the scoring does not take
match length into account).

It uses the termbox library (https://github.com/nsf/termbox).

Build instructions
------------------

Type

    $ make

and you will get a statically linked binary in bin/. Copy wherever you want.
