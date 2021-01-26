# tch-js

An unofficial JavaScript and TypeScript port of PyTorch C++ library (libtorch).

## Install

Package publishing to NPM is still work-in-progress. In the meantime, you can
install the package directly from GitHub.

```sh
$ npm i git+https://github.com/cedrickchee/tch-js.git
```

The package will download the pre-built binary during installation. You don't
have to download PyTorch/libtorch or install tools for compiling from source.

## Versions Supported

- Node.js:
  - 10 (tested)
  - 12 (tested)
  - 14 (WIP)
- PyTorch (CPU):
  - 1.4.X (tested)
  - 1.5.X
  - 1.6.X
  - 1.7.X (tested)

## Code Examples

```javascript
// This is a real example from an audio source separation model.
const { tch } = require('tch-js');
const fs = require('fs');
const wav = require('node-wav');

// WAV samples of length 269973
const monoAudioChan = new Float32Array([
  1.100000023841858, 1.590000033378601,
  2.049999952316284, 0.18000000715255737
]);
// Flat tensor
let audio = tch.tensor(monoAudioChan); // tensor of size [269973]

// Reshape to 1xSample Length to match model input
audio = audio.view([1, monoAudioChan.length]); // tensor of size [1, 269973]

// Load PyTorch traced model async from file and return resulting ScripModule.
tch.load('sound-model.pt', (err, model) => {
  // Forward tensor async and return resulting Tensor.
  model.forward(audio, (err, result) => {
    // result is a tensor of size [1, 1, 269973]
    const out = result.toFloat32Array(); // convert Tensor to JS TypedArray

    // Encode output to 16-bit float WAV and write to file.
    const buf = wav.encode([out], { sampleRate: 44100, float: false, bitDepth: 16});
    fs.writeFileSync("out.wav", Buffer.from(buf));
  });
});
```

## Build It Yourself

Currently, only Linux builds are available.

If you want to build the package youself, below are the steps to reproduce the
build.

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

6. Test

```sh
$ npm run test
```

## The Plan

The library should:
- expose more libtorch types and APIs for inference
- supports Windows
- auto build binaries using CI
- TypeScript types

## Research

- [PyTorch 1.0 tracing JIT and LibTorch C++ API to integrate PyTorch into NodeJS](https://blog.christianperone.com/2018/10/pytorch-1-0-tracing-jit-and-libtorch-c-api-to-integrate-pytorch-into-nodejs/)
- [tch-rs](https://github.com/LaurentMazare/tch-rs) - Rust bindings for the C++ API of PyTorch
- [torch-js](https://github.com/arition/torch-js) - Node.js binding for PyTorch
- [pytorchjs](https://github.com/raghavmecheri/pytorchjs) - Torch and TorchVision, but for NodeJS
- [Using the PyTorch C++ Frontend tutorial](https://pytorch.org/tutorials/advanced/cpp_frontend.html)
- [Loading a TorchScript Model in C++](https://pytorch.org/tutorials/advanced/cpp_export.html)
- [Torchaudio.load() in C++](https://discuss.pytorch.org/t/torchaudio-load-in-c/62400)
- [Minimal PyTorch 1.0 -> C++ full example demo](https://gist.github.com/zeryx/526dbc05479e166ca7d512a670e6b82d)
- [Convert libtorch tensor into an array](https://discuss.pytorch.org/t/convert-tensor-into-an-array/56721)
- [JavaScript TypedArray](https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/TypedArray)
- [Napi::TypedArray](https://github.com/nodejs/node-addon-api/blob/master/doc/typed_array_of.md) - Node.js N-API doc
- [How to use WebAssembly from node.js?](https://stackoverflow.com/questions/51403326/how-to-use-webassembly-from-node-js) - C++ to WebAssembly to Node.js
- [node-pre-gyp](https://github.com/mapbox/node-pre-gyp) - Node.js tool for easy binary deployment of C++ addons
