# gl65

gl65 is a 3D graphics library for 6502-based machine. It aims at providing higly performant ascci art rendering of 3D scene for use in real time applications.

gl65 is born in order to make [glOric](https://github.com/oric-software/glOric) (which is build upon [OSDK](http://osdk.defence-force.org/)) available on [ORIX](http://orix.oric.org/) as well as the multiplatform game SDK [8bit Unity](http://8bit-unity.com/).

gl65 is build upon [cc65](https://cc65.github.io/) developpement chain.


# Build for Oric Atmos

## First method

`make TARGETS=atmos tap`

## Second method

Edit file src/makefile and set value of `PATH_TO_ORICUTRON` and `ODK` to matches your environnement.

```bash
cd src
make
```

then you test the generated tap file by executing:
```bash
make testtap
```