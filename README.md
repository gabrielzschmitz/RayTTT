# RayTTT

<img align="right" width="192px" src="./resources/icon.svg" alt="RayTTT Logo">

<a href="./LICENSE"><img src="https://img.shields.io/badge/license-MIT-green" alt="License"></a>
<a href="https://www.buymeacoffee.com/gabrielzschmitz" target="_blank"><img src="https://www.buymeacoffee.com/assets/img/custom_images/orange_img.png" alt="Buy Me A Coffee" style="height: 20px !important;width: 87px;" ></a>
<a href="https://github.com/gabrielzschmitz/RayTTT.C"><img src="https://img.shields.io/github/stars/gabrielzschmitz/RayTTT?style=social" alt="Give me a Star"></a>

**RayTTT** is a classic TicTacToe game implemented in C++ using the
[raylib](https://www.raylib.com/) framework.  
It features a clean neon retro aesthetic and runs on all major desktop
platforms.

---

## 🎮 Features

- Simple and intuitive gameplay  
- Neon retro visual style  
- Score tracking for players and draws  
- Responsive UI with smooth animations  
- Cross-platform support  

---

## 💻 Supported Platforms

- Windows  
- Linux  
- macOS  

---

## 🚀 Installation & Build

Detailed build and installation instructions for each platform are available in
the dedicated [INSTALL.md](INSTALL.md) guide.

---

## 🛠️ Quick Start

1. Clone the repository:

    ```sh
    git clone https://github.com/gabrielzschmitz/RayTTT.git
    cd RayTTT
    ```

2. Follow the steps in [INSTALL.md](INSTALL.md) for your platform to build and
   run the game.

---

## 🎨 Resources

The project includes a utility that automatically sets the working directory to
the resources folder, simplifying asset loading during development.

---

## ⚙️ Building for Different OpenGL Targets

You can specify the OpenGL version when building the project by modifying the
premake command or scripts. Supported targets include:

- OpenGL 1.1  
- OpenGL 2.1  
- OpenGL 3.3 (default)  
- OpenGL 4.3  
- OpenGLES 2.0  
- OpenGLES 3.0  

Refer to the [INSTALL.md](INSTALL.md) for command examples.

---

## 🧩 Adding External Libraries

TicTacToe keeps dependencies minimal. To add external libraries, modify the
`build/premake5.lua` file using Premake's `links` function.  
More info: [Premake Links Documentation](https://premake.github.io/docs/links/)

---

## 📄 License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file
for full details.
