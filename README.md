# STM32F1Learn

## First Steps

### UBuntu:

#### Install [stlink](https://github.com/texane/stlink#installation)
---

There is no Ubuntu/Debian repository :(, so... we need to build it from source  
build instruction [here](https://github.com/texane/stlink/blob/master/doc/compiling.md)

1. Clone repository (require `git`): `git clone git@github.com:texane/stlink.git`  
or you can download it directly from [github](https://github.com/texane/stlink/archive/master.zip)
2. Install dependencies (cmake, libusb-1.0-0, libusb-1.0-0-dev)
2. Open folder in terminal (Eg. `cd ~/stlink` for home folder)
3. Run `make clear && make release`
4. Install to system: `cd build/Release && sudo make install`
5. Check installation: `st-info --version`

* `export LD_LIBRARY_PATH=/usr/local/lib` - for `libstlink-shared.so` related error

#### Install [STM32CubeMX](http://www.st.com/en/development-tools/stm32cubemx.html) or just [MCUS Embedded Software](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html)
---

I gonna use CubeMX:  
Installation isn't so easy as on windows

1. Download it from link in header
2. Install `java` if you don't have it
3. Extract downloaded `*.zip` file to some folder (Eg. `~/CubeMX`)
4. Run installator: `java -jar SetupSTM32..*.exe` (I want it to be system so I added `sudo`)
5. Default path for me was `/usr/local/STMicroelectronics/STM32Cube/STM32CubeMX`
6. Run CubeMX: `java -jar /usr/local/STMicroelectronics/STM32Cube/STM32CubeMX/STM32CubeMX`

Another [instruction](https://gist.github.com/Lanchon/2156953d18f7534a926b)

7. Install latest (1.6.0) MCUS Embedded Software from CubeMX:
`Help -> Install New Libraries -> STM32CubeF1 Releases`
default installation path can be changed in _udater settings_ menu

#### Install toolchain
---

At least something is easy on Ubuntu ;)

1. Add repository: `sudo add-apt-repository ppa:team-gcc-arm-embedded/ppa`
2. Install: `sudo apt-get update && sudo apt-get install gcc-arm-embedded`

### MacOS
#### Install [stlink](https://github.com/texane/stlink#installation)
---

1. Install dependencies (cmake, libusb-1.0-0, libusb-1.0-0-dev)
2. `brew install stlink`
3. Check installation: `st-info --version`

#### Install [STM32CubeMX](http://www.st.com/en/development-tools/stm32cubemx.html) or just [MCUS Embedded Software](http://www.st.com/content/st_com/en/products/embedded-software/mcus-embedded-software/stm32-embedded-software/stm32-standard-peripheral-libraries/stsw-stm32054.html)
---

I gonna use CubeMX:  
Installation isn't so easy as on windows

1. Download it from link in header
2. Install `java` if you don't have it
3. Extract downloaded `*.zip` file to some folder (Eg. `~/CubeMX`)
4. Open folder => select `*.app` file => show package contents 
5. Open `Contents/MacOs` and 2-x click on file inside this folder
6. Install latest (1.6.0) MCUS Embedded Software from CubeMX:
`Help -> Install New Libraries -> STM32CubeF1 Releases`
default installation path can be changed in _udater settings_ menu

#### Install toolchain
---

1. `brew cask install gcc-arm-embedded`

**CONGRATULATIONS!!! Now your machine is ready to make some STM32F1 project**

## Preparing code
### Ubuntu & MacOS
---

1. `git clone git@github.com:rtm7777/stm32_learn.git`
2. Open `CMakeLists.txt` file
3. Set `STM32CubeF1_FW` to your installation path
4. Set `CMAKE_C_COMPILER` `CMAKE_LINKER` `CMAKE_OBJCOPY` `CMAKE_SIZE` to your installation path
5. `cmake ./`
6. `make`
7. Run `st-util`
8. Run `arm-none-eabi-gdb` in separate terminal tab
9. Enter `tar extended-remote :4242` in debugger to connect it
10. Flash `*.elf` file `load stm32learn.elf`
11. Enter `continue` to run firmware

* To just write binary file: `st-flash write stm32learn.bin 0x8000000`
