fuzzyfinder
============

Fuzzy select among lines in stdin. Lines are filtered according to an
interactive query inputed by the user. The selected line will be
outputed to stdout. A line matches a query if the query is a subsequence
of the line.

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

TODO
----

* ~~Queries cannot contain spaces. Don't know why it does not work.~~
* If there are a lot of lines only the first screenful will show.
* ~~Long lines could break the program (they try to be printed but screen can't hold them)~~
* ~~Add UTF-8 support.~~. Add UTF-8 query strings (gotta check with termbox).
* Remove GNU C99 dependency on _getline_.
* Profile and optimize the code.
* Refactor main.c
