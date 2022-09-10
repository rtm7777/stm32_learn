# STM32F1Learn

## First Steps

### UBuntu:
---
#### Install [STM32CubeMX](https://www.st.com/en/development-tools/stm32cubemx.html)

1. Download zip archive
2. Extract it somewhere
3. Doudle click on `SetupSTM32CubeMX-XXX` file and follow instructions
4. Go to installation folder and Run CubeMX

5. Install latest (1.8.4 atm) MCUS Embedded Software from CubeMX:
`Help -> Manage embedded software packages -> STM32F1`
default installation path can be changed in _udater settings_ menu

---
### Install VSCode Extensions

1. [C/C++](https://github.com/Microsoft/vscode-cpptools)
2. [Cortex Debug](https://github.com/Marus/cortex-debug)
3. [Makefile Tools](https://github.com/Microsoft/vscode-makefile-tools)

---
#### Install [stlink](https://github.com/stlink-org/stlink#installation)

1. Go to releases and download `*.deb` package
2. Install it with `sudo dpkg -i stlink_*.deb`
3. In case of missing packages run this command `sudo apt-get -f install`
4. Check installation: `st-info --version`

* `export LD_LIBRARY_PATH=/usr/local/lib` - for `libstlink-shared.so` related error

---
#### Install tools

1. Install `xpm` if you don't have it: https://xpack.github.io/xpm/install/
2. Run `xpm install` command

---
#### Get latest SVD file for our processor on st.com

- in case of our "blue pill" STM32F103 the link is: [here](https://www.st.com/en/microcontrollers-microprocessors/stm32f103.html#cad-resources)
1. add `STM32F103.svd` file to the root folder


## Interesting articles
- [CUSTOM ST-LINK V2.1](http://embedblog.eu/?p=780)