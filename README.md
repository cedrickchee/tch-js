# tch-js

An unofficial JavaScript port of PyTorch C++ frontend (libtorch).

## Versions Supported

- Node.js:
  - 10 (tested)
  - 12 (tested)
  - 14 (WIP)
- PyTorch:
  - 1.4.X (tested)
  - 1.5.X
  - 1.6.X
  - 1.7.X (tested)
- OS:
  - Linux (tested)
  - Windows (WIP)

## Build It Yourself

We have pre-built binaries. If you want to build the package youself, below are
the steps to reproduce the build.

Installing on Linux:
- Ubuntu 18.04 (tested)
- Ubuntu 20.04 (tested)

1. Install build tools

```sh
$ apt install -y cmake make gcc-c++ unzip
```

2. Install Node.js 10
3. Download libtorch
Download [libtorch pre-cxx11 ABI and CPU version](https://pytorch.org/get-started/locally/#start-locally).

```sh
$ curl -o libtorch.zip https://download.pytorch.org/libtorch/cpu/libtorch-shared-with-deps-1.7.1%2Bcpu.zip
$ unzip libtorch.zip
```

4. Install Node.js packages

```sh
$ npm i --ignore-scripts
```

5. Build

```sh
$ npm run pre-build
```
