# peephole

Winner of the 2016 Peephole Optimization contest for Java bytecode, by Group 05 for COMP 520 (McGill). (`spec.pdf` contains the details of the contest.)

To compile and run the 7 benchmarks with the peephole patterns (inside `JOOSA-src/patterns.h`), and produce a report of the optimizations, set a `PEEPDIR` environment variable to the location of the project directory and simply run `make` inside the directory. This will JOOS compile each of the benchmarks using the patterns, and then run the JUnit test suite to ensure all benchmarks properly run.

(This project is not yet set-up for a Windows machine.)
