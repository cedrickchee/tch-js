# tch-js

An unofficial JavaScript port of PyTorch C++ library (libtorch).

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
const tch = require('tch-js');
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

## The Plan

The library should:
- expose more libtorch types and APIs for inference
- supports Windows
- auto build binaries using CI
