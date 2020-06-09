# gl65

gl65 is a 3D graphics library for 6502-based machine. It aims at providing higly performant ascii art rendering of 3D scene for use in real time applications.

gl65 is born in order to make [glOric](https://github.com/oric-software/glOric) (which is build upon [OSDK](http://osdk.defence-force.org/)) available on [ORIX](http://orix.oric.org/) as well as the multiplatform game SDK [8bit Unity](http://8bit-unity.com/).

gl65 is build upon [cc65](https://cc65.github.io/) developpement chain.



# Build for Oric Atmos

## First method

In root directory, run the following command:

`make TARGETS=atmos tap`

## Second method

Edit file src/makefile and set value of `PATH_TO_ORICUTRON` and `ODK` to matches your environnement.
NB: `ODK` is only required if you plan to produce a `.dsk` file rather than a `.tap` file.

```bash
cd src
make
```

then you can test the generated `main.tap` file by executing:
```bash
make testtap
```

# Build for Orix

Building gl65 for Orix consists in compiling for `telestrat` target.

In root directory, run the following commands:

```bash
make TARGETS=telestrat
cp gl65.telestrat /path/to/Orix/usbdrive/bin/demoGl65
```

Now you can open your Orix and run the following command:

```bash
demoGl65
```


# Build for Commodore 64

In root directory, run the following command:

```bash
make TARGETS=c64 prg
```

This build a `gl65-c64.prg` that you can open with VICE
