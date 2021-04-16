# BrainFry
It's a header-file only BrainFuck interpreter, the name is too profane to share in social media. A very simple one designed to teach how to create an interpreter, 
explain how Turing Machines work and the relation between the language and Turing machines.

Blog explaining the underlying theory: https://pixeltrik.vercel.app/blogs/turing-machines-and-brainfry

## Usage
This one is a header-only library, to see how to use and include, refer to `main.cpp`. This is meant to be a generic interpreter, so you can use other I/O streams 
like file streams or string streams if you don't want to use console streams (standard I/O).

```
    // Some Hypotheical Code Snippet

    ifstream input("input-file");
    sstream output;

    BrainFry brainfry;
    brainfry.parse(code, input, output);

    string str = output.str();

    // To reset the states of the interpreter
    
    brainfry.reset();

    // ...
```

To reset the interpreter, use `reset()` function to remove all states and clean the stack too.
Just like other modern C++ programs, you can compile it using `g++` or `clang++`. 

## Running the example
In this repository, I have included a simple "Hello, World!" program (which is difficult in this language). 
With Clang, compile using
```
clang++ main.cpp -o brainfry
```

With GCC, compile using
```
g++ main.cpp -o brainfry
```

And use the program using
```
cat hello-world.bf | ./brainfry
```
