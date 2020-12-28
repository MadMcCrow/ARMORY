# ARMORY

Armory is a RTS inspired by abandonware _Arsenal : Taste The Power_

> A.R.S.E.N.A.L Taste the Power is a real-time strategy game created by Tactical Software for MS-DOS and released as shareware in 1997. A.R.S.E.N.A.L is still sold by its legal owner, but it is not compatible with modern OSes without some form of emulation of past hardware (ie. DosBox).

## Godot project

This project is made with the Godot Engine (here pronounced _/ˈɡɒdoʊ/_ _GOD-oh_) built from source with a `custom.py` file passing arguments to `scons` (the build tool).

### Setup on your device

to set the project up on your device just clone this repository and run the following:
   
```
git submodule update --init # update/get the godot submodule
make # or python build/setup.py
```
if this does not work for you, I suggest you check [`build/config.json`](build/config.json) and [`build/custom.py`](build/custom.py) to see if anything is not compatible with your current configuration.


### Modular approach

The game will be (almost) entirely in C++. the code is added to modules in the sources folder.

## Help and Participate.

Any push request will be treated, and merged if it's any kind of improvement or bug fix.
You can also fork this project and make a game of your own.

## git emoji table used : 

| emoji             | commit contains               |
| ------------------|:-----------------------------:|
| :zap:             | improvement                   |
| :construction:    | WIP                           |
| :art:             | graphical asset               |
| :wrench:          | update build system           |
| :no_entry_sign:   | does not compile / launch     |
| :page_facing_up:  | update of doc, licence, etc.  |


## Big thanks to :

- @Zylann and the whole [godot discord](https://discord.com/invite/4JBkykG) for their help

## License

Copyright © Noé Perard-Gayot 2020.    
Licensed under the [MIT License](LICENSE.txt)
You may also obtain a copy of the License at https://opensource.org/licenses/mit-license.php 
