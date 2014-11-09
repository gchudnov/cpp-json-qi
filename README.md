cpp-json-qi
===========

A C++ JSON header-only library, implemented with Boost.Spirit

### Directories

* **build** - directory for tests & examples
* **examples** - examples source code
* **include** - the source code of the library
* **test** - test source code

### More information

* [Wiki](https://github.com/gchudnov/cpp-json-qi/wiki)

### Tested compilers

* Linux (x86/64)
   * GCC 4.8, Boost 1.54
   * Clang 3.4, Boost 1.54
* Windows (x86/64)
   * MSVC 14, Boost 1.57

### Installation

This is a header only library, in order to use it make the cpp-json-qi-`include` directory available to your project and  include the header file in your source code:

```c++
#include "cpp-json-qi/json.h"
```

### Building Tests & Examples

This project tests and examples use the Cross-platform Make ([CMake](http://www.cmake.org/)) build system.
Tests depend on [Google Test Framework](https://code.google.com/p/googletest/)

#### Linux

The recommended way is to create 'out of source' build:

```
cd cpp-json-qi/build
cmake ..
make
```

#### Windows

If using Visual Studio:
 
    Follow the directions at the link for running CMake on Windows:
    http://www.cmake.org/runningcmake/
    
    NOTE: Select the "build" folder as the location to build the binaries.


### Deleting all the files that a Make & CMake has produced 

```
make clean-all
```

### Contact

[Grigoriy Chudnov] (mailto:g.chudnov@gmail.com)

### License

Distributed under the [The MIT License (MIT)](https://github.com/gchudnov/cpp-json-qi/blob/master/LICENSE).
