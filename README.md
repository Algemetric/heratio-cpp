# HERatio
Algemetric's Fully homomorphic encryption scheme with Hensel Codes. 
HERatio stands for **H**omomorphic **E**ncryption over **Ratio**nals.

# Overview

HERatio is written in C++ and is built using [Bazel](https://bazel.build/). 

If you are on Mac, you can install Bazel using Homebrew:

```bash
brew install bazel
```

There are also other options for [installing Bazel on Mac](https://bazel.build/install/os-x). If you are on Linux, there are [several options available](https://bazel.build/install) depending on what distribution you use. Some spefic recommendations for Ubuntu can be found [here](https://bazel.build/install/ubuntu). Instructions for [installing Bazel on Windows](https://bazel.build/install/windows) are also available.

Bazel also offers [Bazelisk](https://bazel.build/install/bazelisk), a tool with which you can easily install Bazel on Ubuntu, Windows, and Mac. 

## Dependencies

In order to properly compile and run HERatio, you need to have [NTL](https://libntl.org/) and [GMP](https://gmplib.org/) in your system. 

If you are on Mac, you can use [Homebrew](https://brew.sh/) to install both [NTL](brew install ntl) and [GMP](https://formulae.brew.sh/formula/gmp) as follows: 

```bash
brew install ntl
brew install gmp
```

If you are on Linux, you can follow these instructions for installing and configuring [NTL](https://libntl.org/doc/tour-unix.html) and [GMP](https://gmplib.org/manual/Installing-GMP). You can find the latest packages for dowloading GMP [here](https://gmplib.org/#DOWNLOAD). 

If you are on Windows, you can follow these instructions for installing and configuring [NTL](https://libntl.org/doc/tour-win.html) and [GMP](https://gmplib.org/#DOWNLOAD). 

Once you have NTL and GMP in your system, make sure to modify the path for both libraries inside the file `WORKSPACE` at the root of the project:

```c++
new_local_repository(
  name = "ntl",
  path = "/usr/local/var/homebrew/linked/ntl",
  build_file = "dependencies/BUILD.ntl",
)

new_local_repository(
  name = "gmp",
  path = "/usr/local/var/homebrew/linked/gmp",
  build_file = "dependencies/BUILD.gmp",
)
```

The paths above will work if you installed NTL and GMP using Homebrew. Otherwise, just replace these paths by the corresponding paths in your system.

# Building, Running, Cleaning up, and Testing

Building:

```bash
bazel build demo:heratio
```

Running demo:

```bash
./bazel-bin/demo/heratio
```

Cleaning up:

```bash
bazel clean
```

Testing:

```bash
bazel test --test_output=all //...
```

