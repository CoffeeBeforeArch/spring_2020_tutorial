# Hardware, Software, and Compilers! Oh My!

This repository contains all code/links to all examples presented in the Spring 2020 "Hardware, Software, and Compilers! Oh My!" tutorial. I've provided a breakdown of all of the topics below, along with supplemental links for those interested.

Cheers,

Nick

## The Small Buffer Optimization
Dynamic allocations are expensive, and we'd like to avoid them (if possible). One way we can do this is the small buffer optimization. We can leave some extra space inside of a handle to a larger dynamic allocation (like a std::string) where we can store a small number of elements. By doing this, we can defer any dynamic allocation until we run out of space inside the handle. All major compilers implement a form of this optimization for std::string in C++ (but interestingly, they don't all do it the same way!). In this example, we will be looking at a few implementations of the small buffer optimization (known as the short/small string optimization), and benchmarking the cost of dynamic allocation.

[Short string optimization source code](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/sso)

### Relevant Links
[The strange details of std::string at Facebook](https://youtu.be/kPR8h4-qZdk)

## Copy Elision
Copying a large object can be expensive. Compiler writers understand this, and have been implementing optimization passes for copy elision to remove unnecessary copies. A common form of this is the Return Value Optimization (RVO) and Named Return Value Optimizaiton (NRVO). These deal with eliding the copy of an object during a function return. However, you're compiler can't always elide the copy! In this example, we will look at some source and disassembly of a simple function to better understand RVO, and when/where it may not be applicable

[Source and Disassembly](https://godbolt.org/z/aQqHns)

### Relevant Links

[Copy elision in the C++ standard](https://en.cppreference.com/w/cpp/language/copy_elision)
[Arthur O'Dwyer's 2018 CppCon Talk](https://youtu.be/hA1WNtNyNbo)

## Aliasing

Compilers are smart, and can exploit opportunties that even the most veteran of programmers can't notice. However, compilers aren't omniciant, and this can lead them to being overly conservative. A great example of this is aliasing. If a compiler can not figure out if two references point to the same piece of memory, it may not be able to perform certain optimizations (e.g, vectorization). In this example, we will look at the source and disassembly of a simple function, and measure the performance impact of aliasing on a simple matrix multiplication CUDA kernel.

[Source and Disassembly](https://godbolt.org/z/oYev9z)
[CUDA Matrix Multiplication](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/matrix_mul)

### Relevant Links
[Strict aliasing in C++](https://gist.github.com/shafik/848ae25ee209f698763cffee272a58f8)
[Aliasing in CUDA](https://devblogs.nvidia.com/cuda-pro-tip-optimize-pointer-aliasing/)
