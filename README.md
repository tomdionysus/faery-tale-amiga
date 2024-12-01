# The Faery Tale Adventure - Amiga

This repository contains the source code to the original "The Faery Tale Adventure" published
by MicroIllusions on the Amiga in 1987. It was written by me (Talin) over the course of seven
months.

## State of the code

This code was written very early in my programming career, and in a hurry; the code is of generally
poor quality with few comments. I don't remember very much about it, and probably won't be able
to give useful answers to questions about it.

The code is primarily written in Aztec C, with some 68000 assembly.

I don't know whether it would be possible to actually get the game running on some other platform;
but even so the code may have some historical interest.

## 2024 Modifications
In late 2024, after @viridia [open-sourced the game code](https://www.reddit.com/r/retrogamedev/comments/1gs2xzu/source_code_for_the_original_faery_tale_adventure/), 
[Troy Tarrant](https://github.com/ttarrant) and [Tom Cully](https://github.com/tomdionysus) created 
this fork to hack on the game using emulated FS-UAE Amigas.

Our modifications to the orginal code are listed in the [CHANGELOG](CHANGELOG.md).

As of 1st Dec 2024, this branch builds a working game with copy protection removed:

### Building The Game

This guide assumes building under Aztec C68k/Amiga 5.2a on an Amiga A500 Kickstart 1.3 with 512k
Chip RAM and 512k Slow Ram (FS-UAE) and a 20MB hard disk (dh0).

* Aztec C is installed at `dh0:Aztec`
* The game code is in `dh0:faery`

### Aztec C Toolchain

Once Aztec C is installed, various path and environment variables need to be set up. Assuming a 
standard installation in `dh0:Aztec`, there is a script supplied to do this, which appears to have
a bad include path for assembler. You should modify the `dh0:Aztec/aztec.sh` file as follows:

```
path "DH0:Aztec/bin"
mset CCTEMP=ram:
mset "CLIB=DH0:Aztec/lib/libs"
mset "INCLUDE=DH0:Aztec/include;DH0:Aztec/incl_asm
```

Then, execute it to setup your paths:

```sh
execute dh0:Aztec/aztec.sh
```

To save time, you can add this line to the end of your `s/Startup-Sequence` file to set up the 
paths on boot:

```
...rest of file...

execute dh0:aztec/aztec.sh
LoadWB delay  ;wait for inhibit to end before continuing
endcli >NIL:
```

### Precompiling `amiga39.pre`

Aztec C allows the generation of precompiled headers. The game `makefile` requires `amiga39.pre`
to be precompiled, which can be done like so:

```sh
cd dh0:faery
cc -ho amiga39.pre fincludes.c
```

### Compiling

The build can be initiated by simply using the `make` command in the correct directory. 

```sh
cd dh0:faery
make
```

**NOTE:** If running under an emulator (FS-UAE, WinUAE) compliation time can be dramatically
reduced (from 30m to a few seconds) by compiling on an Amiga equipped with a 68030 CPU or 
higher.

### Running

The executable `fmain` must be started with the current directory set to the `game` folder:

```sh
cd dh0:faery/game
/fmain
```

## Copyright status

Under U.S. Copyright law, a creator may reclaim the copyright of their work after 35 years,
a process known as "termination of transfer". Accordingly, in 2022 I sent a termination of transfer
notice to Hollyware, Inc., the successors-in-interest to the intellectual property of
MicroIllusions. Unfortunately, they have not responded to my letter or any other inquiries I have
made over the years.

Thus, I cannot say for certain exactly what the copyright status of this code is. However, whatever
rights I do have, I hereby make freely available under an MIT-style permissive license.