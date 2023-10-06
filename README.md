# weak-symbols

A minimal example of weak symbol linking problems. See
https://issues.pigweed.dev/303846960 for context.

## Cloning

After cloning the repository, run `git submodule --update init` to get the
Pigweed submodule (can't be pulled in via WORKSPACE for obscure reasons,
https://issues.pigweed.dev/300695111).

## Building

If you run,

```
bazel run :main
```

Bazel will build the binary with the hermetic clang configured in upstream
Pigweed,
[here](https://cs.opensource.google/pigweed/pigweed/+/main:pw_toolchain/host_clang/BUILD.bazel),
and then run it.

If you run,

```
bazel build --platforms=//targets:cortex-m4 :main
```

Bazel will build the binary with Arm GCC, configured
[here](https://cs.opensource.google/pigweed/pigweed/+/main:pw_toolchain/arm_gcc/BUILD.bazel).

## Results

In the code-as-checked-in everything looks fine:

1.  The binary built with the host clang prints,

    ```
    Calling A
    strong A!
    ```

2.  I ran `nm --demangle` on the binary produced by Arm GCC, via

    ```
    $(bazel info output_base)/external/gcc_arm_none_eabi_toolchain/bin/arm-none-eabi-gcc-nm --demangle bazel-bin/main > /tmp/nm.txt
    ```

    The output includes the line,

    ```
    00008164 T A
    ```

    This indicates that the strong symbol was correctly linked in.

But you can break the program by adding `__attribute((weak))__` to the function
declaration in `weak.h`. It will still compile, but at runtime you'll get a
segmentation fault (with host clang). And `nm` on the Cortex-M4 binary shows no
entry for `A` at all.
