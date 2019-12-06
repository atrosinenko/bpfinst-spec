# Specification for my eBPF-based instrumenters

This repository contains the specification for different implementations of eBPF-based instrumentation engines.

**Status:** alpha, compatibility can be broken at any time.

## Implementations

* QEMU-based: [QInst](https://github.com/atrosinenko/qinst) **(update is pending)**
  * dynamic binary instrumentation
  * handles user-mode executables (including foreign hardware architectures)
  * supports tag propagation
* RISC-V soft-processor based: [SimpleInst](https://github.com/atrosinenko/simpleinst) **(update is pending)**
  * instrumentation is statically built into an instance of RocketChip soft-processor during Verilog generation
* LLVM-based: [LLInst](https://github.com/atrosinenko/llinst)
  * static white-box instrumentation
  * implemented as an LLVM pass
  * supports tag propagation

## Design goals

Unlike [DynamoRIO](https://www.dynamorio.org/), this is not a generic instruction list rewriter API.
While the native API looks quite similar to DR sometimes, the main purpose here is to implement simple per-instruction instrumentations as simple as possible. An instrumenter is just a set of not-too-complex (generally, with static forward branches only) functions in C that perform what you want for some basic operations from the original program (arithmetic, logic, branching, ...) and some native library with slow path callbacks.

## Tags

Some implementations support abstract propagation of 64-bit-wide tags. The format of tag is completely user-controlled with the exception for 0 being default value when no tag is available. The implementation for storing tags in the address space of program is user-controlled, too:
* dense storage: tags may be stored in another address space of equal size
* sparse storage: only allocated tags may be stored in some (expected to be small) data structure
* etc...

## How to use this repository

This repository is expected to be added to the engine implementation repository as a submodule named `bpfinst-spec`. On the same hierarchy level a directory named `bpfinst-bin` should be located with the following scripts:
* `prepare-for-test`
  * is executed before any tests are performed, so the instrumenter itself can be built with this particular instrumentation
  * for example, to build an instrumenting instance of a soft-processor
* `compile-sources <program> <arg1> <arg2> ...`
  * should set environment variables (such as `CC`, `CFLAGS`, `CXX`, `CXXFLAGS`, `LD`, `LDFLAGS`, ...) for its subprocess
  * for example, to properly build a program in a static instrumentation setup
* `run-binary <program> <arg1> <arg2> ...`
  * starts the compiled program under instrumentation
  * for example, to run a regular program under dynamic instrumenter
