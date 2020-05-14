# SFML Game of Life

This project is utilizing CMake to generate build systems.

## Controls

I haven't bothered adding a GUI library or creating one.  But, here are some keyboard commands to control the "game":

`escape` - Quits the program

`r` - Starts a new seed.  If you run the executable from a terminal, you will see your new seed.

`space` - Pause / resume simulation

## Install dependencies

### Mac OS X

First setup homebrew: https://brew.sh/

`brew install sfml`

### Linux

`sudo apt-get install libsfml-dev`

## Unix/Linux make build

Create a new folder to place the built files into.

`mkdir build`

Change directories.

`cd build`

Generate the make build system.

`cmake ..`

Compile

`make`

And install, this will setup the `*.app` on OS X by copying libs over and changing their linked paths.  

`make install` or `sudo make install`

Note: If you see errors about like

`install_name_tool: can't open input file: ..libvorbis.0.dylib for writing (Permission denied)`

Then you may need to run `make install` with sudo like `sudo make install`

