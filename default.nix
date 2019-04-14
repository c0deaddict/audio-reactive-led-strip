{ nixpkgs ? import <nixpkgs> {} }:

with nixpkgs;
with lib;

let

  python = python37;
  pythonPackages = python37Packages;

  pythonEnv = python.buildEnv.override {
    extraLibs = with pythonPackages; [
      numpy
      scipy
      pyaudio
      pyqtgraph
    ];
  };

in

mkShell {
  name = "audio-reactive-led-strip";

  buildInputs = [
    pythonEnv
  ];
}
