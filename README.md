cpp-json-qi
===========

A C++ JSON header-only library, implemented with Boost.Spirit

### Directories

* **bin** - project executables (tests & examples)
* **examples** - cpp-json-qi examples
* **include** - the sourcecode of cpp-json-qi
* **test** - cpp-json-qi unit tests

### More information

* [Wiki](https://github.com/gchudnov/cpp-json-qi/wiki)

### Tested compilers

* Linux (x86/64)
   * GCC 4.8, Boost 1.54
   * Clang 3.4, Boost 1.54

### Building

cpp-json-qi tests depend on [Google Test Framework](https://code.google.com/p/googletest/)

To build all tests & examples:

```
cd cpp-json-qi
cmake .
make
```

### Building 'out of source'

To create `out of source` build, invoke: 

```
cd cpp-json-qi
mkdir build
cd build
cmake ..
make
```

### Deleting all the files that a Make & CMake has produced 

```
make clean-all
```

### Contact

[Grigoriy Chudnov] (mailto:g.chudnov@gmail.com)

### License

Distributed under the [The MIT License (MIT)](https://github.com/gchudnov/cpp-json-qi/blob/master/LICENSE).
