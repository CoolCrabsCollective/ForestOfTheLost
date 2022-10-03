# Forest of the Lost
This project is meant to be a ready to run WizEngine template project for Windows, Linux and Switch. You can clone or fork this repo and start making your game. All dependencies (SFML, WizEngine) are handled by the project.

# Deploying the client

## Desktop

### Building

```
cd client
cmake -B build -S .
cd build
make
cd ..
```

This will produce an executable and copy required assets in the folder `client/bin/<your platform>/`. (e.g. `client/bin/linux64` on 64 bits Linux systems)

### Executing

```
cd bin/<your platform>/
./<Executable name> # Name will change according to your project name
```

Make sure you distribute all files that are in the `bin/<your platform>` folder. .so, .dll and res/ folder are all required by the game.

## Switch

### Development setup

This development setup only needs to be done once for the Switch. After this you can just build according to the method below.

#### Install Pacman

For Ubuntu:

Download Debian install package [here](https://github.com/devkitPro/pacman/releases/tag/v1.0.2)

* `sudo dpkg -i devkitpro-pacman.amd64.deb`

For ArchLinux:

Customize your existing pacman installation using this guide: https://devkitpro.org/wiki/devkitPro_pacman

#### use Pacman to install devkitA64 for compilation toolchains
* `sudo dkp-pacman -S switch-dev`
  (Hit enter to use all repositories by default)

