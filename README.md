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

[Source and disassembly](https://godbolt.org/z/aQqHns)

### Relevant Links

[Copy elision in the C++ standard](https://en.cppreference.com/w/cpp/language/copy_elision)

[Arthur O'Dwyer's 2018 CppCon Talk](https://youtu.be/hA1WNtNyNbo)

## Aliasing and Compiler Optimization

Compilers are smart, and can exploit opportunties that even the most veteran of programmers can't notice. However, compilers aren't omniciant, and this can lead them to being overly conservative. A great example of this is aliasing. If a compiler can not figure out if two references point to the same piece of memory, it may not be able to perform certain optimizations (e.g, vectorization). In this example, we will look at the source and disassembly of a simple function, and measure the performance impact of aliasing on a simple matrix multiplication CUDA kernel.

[Source and disassembly](https://godbolt.org/z/oYev9z)

[CUDA matrix multiplication source code](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/aliasing)

### Relevant Links
[Strict aliasing in C++](https://gist.github.com/shafik/848ae25ee209f698763cffee272a58f8)

[Aliasing in CUDA](https://devblogs.nvidia.com/cuda-pro-tip-optimize-pointer-aliasing/)

## Link Time Optimization (LTO)

Changing how we compile a program can change it's performance. One example of this is when we break our compilation into multiple translation units. Because the compiler doesn't have the full context of the program, it may omit some optimizations. However, we can get some of these optimizations back at link time using Link Time Optimization (LTO). In this example, we will look at how the compiler optimizes a matrix multiplication benchmark in a single translation unit, split across two translation units, and split across multiple translation units with Link Time Optimization enabled.

[CPU matrix multiplication source code](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/lto)

### Relevant Links

[GCC's Link Time Optimization](https://gcc.gnu.org/onlinedocs/gccint/LTO-Overview.html)

## Branch Prediction

Modern processors rely on branch predictors to keep the pipeline filled in the presence of branches. However, the programmer has a cruicial role in helping out the branch predictor. If we are able to write more predictable code, the branch predictor is able to speculate better. However, if our branches become somewhat random, we can suffer sever performance penalties. In this example we will take a look at the role of branch prediction with virtual functions/dynamic dispatch. We will benchmark different orderings of virtual function calls, and study the affects on the branch miss prediction rate.

[Virtual function source code](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/branch_prediction)

### Relevant Links

[Agner Fog's Assembly Optimization Guide](https://www.agner.org/optimize/optimizing_assembly.pdf)

[Agner Fog's Optimizing C++](https://www.agner.org/optimize/optimizing_cpp.pdf)

## Code Scheduling

The dynamic order of instructions can have a significant impact on performance. One example of this is with branches. Preferring one side of a branch over another can lead to significant performance differences. In this example we will look at using a compiler intrinsic to give hints as to what the "hot-side" of a branch is, and measure the performance difference.

[Link to modulo benchmark](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/instruction_scheduling)

### Relevant Links

[Anger Fog's Instruction Tables](https://www.agner.org/optimize/instruction_tables.pdf)

[Chandler Carruth's 2015 CppCon Talk](https://youtu.be/nXaxk27zwlk)

## Cache Associativity

Caches are critical to providing performance in modern processors. However, seemingly innacuous access patterns can lead to unexpected drops in performance. One example of this is a power-of-two stride. Modern caches are set-associative (each cache line gets mapped to a set, but there are only N ways where it can be placed). When we do a power of two set, we stumble across the relatively simple mapping of cache lines to sets. As we increase the power of two, the number of unique sets we access decreases, until every cache line we access maps to the same one. In this example, we will show how we can predict such access patterns for an arbitrary processor by looking at the cache organization details.

[Link to associativity benchmark source code](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/associativity)


### Relevant Links

[What Every Programmer Should Know About Memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)

## Prefetching

Not all access patterns have the same performance. As we showed in the cache associativity example, power-of-two stride can lead to unfortunate performance consequences. Another part of the hardware we should think about is the prefetcher. If we have a constant stride access pattern, our hardware prefetcher can begin fetching cache lines before we need them. However, more random access patterns do not get this benefit. In this example, we will be looking at a number of different access patterns to explore the limits of hardware prefetching, and briefly discuss software prefetching intrinsics.

[Link to prefetching benchmark](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/prefetching)


### Relevant Links

[Stony Brook University lecture on prefetching](https://compas.cs.stonybrook.edu/~nhonarmand/courses/sp15/cse502/slides/13-prefetch.pdf)

[What Every Programmer Should Know About Memory](https://people.freebsd.org/~lstewart/articles/cpumemory.pdf)

## False Sharing

2004 marked the beginning of the multi-core era, as Intel cancelled a 4GHz Pentium 4 processor in favor of dual core. Since that time, all major processor vendors have focused on multi-core performance over single-core. Optimizing multithreaded applications is difficult. Poorly implemented synchronization strategies can lead to execution times that look worse than if the program was single-threaded. However, some performance pitfalls can be more subtle. One of these is false sharing. In this example, we will show how false sharing can impact performance, and briefly discuss the role of coherence in performance. 

[Link to false sharing benchmark](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/false_sharing)

### Relevant Links

[Intel blog on false sharing](https://software.intel.com/en-us/articles/avoiding-and-identifying-false-sharing-among-threads)

## SIMD Intrinsics - An Optimization Case Study

The majority of comput hardware on modern processors is in the vector units. While compiler-based vectorization can typically achieve ~80% maximum performance, there may be situations where we need to take matter into our own hands. However, knowing _if_ you should be applying vectorization is another story. In this example, we will be examining the optimization of matrix-vector multiplication. We will explore whether we are compute or memory-bound, then manually apply some vectorization to boost performance.

[Link to matrix-vector benchmark](https://github.com/CoffeeBeforeArch/spring_2020_tutorial/tree/master/matrix_vector)


[Vectorized Dot Product Intrinsic](https://software.intel.com/sites/landingpage/IntrinsicsGuide/#text=_mm256_dp_ps&expand=2185)

### Relevant Links

[Intel Intrinsics Guide](https://software.intel.com/sites/landingpage/IntrinsicsGuide/#)
