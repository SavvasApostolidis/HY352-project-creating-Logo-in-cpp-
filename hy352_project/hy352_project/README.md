HY352 Project - Logo GUI
========================


**This file contains instructions for installing Allegro and building the demo project.**

**For the API guide, see [Documentation.md](Documentation.md).**

---


## Windows

Build and run using Visual Studio.

#### Create an empty project

* Open the project creation dialog: **File → New → Project...**
* Opt for an empty project: **Visual C++ → General → Empty Project**

#### Install Allegro using NuGet

* Right-click on your project and select **Manage NuGet Packages**.
* Go to the **Browse** tab and search for **Allegro** using the search bar.
* Locate **Allegro** package and press **Install**.

#### Configure Allegro

* Right-click on your project and select **Properties**.
* Select **Allegro 5** and set the **Library type** to **Dynamic Debug - Dynamic Runtime**.
* Now enable the required **Add-ons**:
    * **Image**
    * **Font**
    * **TrueType Font**
    * **Primitives**
    * **Color**
* Hit the **Apply** button.


## Linux

#### Install Allegro

##### Ubuntu 18.04+

```sh
sudo apt install liballegro*5.2 liballegro*5-dev
```

##### Fedora

```sh
sudo dnf install allegro5*
```

##### Other distros

Search with your package manager for a binary package or build from source, if none is available (see **Getting Started** guide at the bottom of this page).

#### Compiling from terminal

```sh
g++ -std=c++11 hy352_gui.cpp example.cpp -o hy352_demo $(pkg-config --libs allegro-5 allegro_image-5 allegro_primitives-5 allegro_font-5 allegro_ttf-5)
```


## macOS

**It seems NOT to work on macOS. Please, try on Windows or a Linux VM.**

---

#### Install Homebrew

```sh
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

#### Install Allegro

```sh
brew install allegro
```

#### Compiling from terminal

```sh
clang++ -std=c++11 hy352_gui.cpp example.cpp -o hy352_demo -lallegro -lallegro_primitives -lallegro_image -lallegro_ttf -lallegro_font -lallegro_main
```

#### Using Xcode

Open `./projects/xcode/LogoGUI.xcodeproj`.


## Resources

* [Getting Started with Allegro - Allegro Wiki](https://wiki.allegro.cc/index.php?title=Getting_Started)