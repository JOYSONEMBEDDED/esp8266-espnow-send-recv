# ESP8266 ESPNOW SEND & RECEIVE

This repository contains ESPNOW SEND and RECEIVE examples
using the ESP8266 RTOS SDK.

## Folder Structure

- espnow_send : ESPNOW transmitter example
- espnow_recv : ESPNOW receiver example

## SDK Used
ESP8266_RTOS_SDK

## Author
Joyson Vashikaran

ESP8266 RTOS SDK – MSYS2 (MINGW32) Setup Guide

This project uses the ESP8266 RTOS SDK and is built using MSYS2 MINGW32 shell.

1️⃣ Prerequisites
Software Required

Windows 10 / 11

Git

Python 3.x

MSYS2

ESP8266 RTOS SDK

ESP8266 Xtensa Toolchain

USB-to-UART driver (CP210x / CH340)

2️⃣ Install MSYS2

Download MSYS2 from:
👉 https://www.msys2.org/

Install it (default location recommended):

C:\msys32


Open MSYS2 MINGW32 Shell (⚠️ important — not MSYS, not UCRT).

Update MSYS2 packages:

pacman -Syu


Restart shell if asked.

3️⃣ Install Required Packages in MINGW32
pacman -S --needed \
mingw-w64-i686-toolchain \
mingw-w64-i686-cmake \
mingw-w64-i686-python \
git make

4️⃣ Install ESP8266 RTOS SDK

Clone the SDK:

cd ~
git clone https://github.com/espressif/ESP8266_RTOS_SDK.git


SDK location:

/c/msys32/home/hprcse/esp/ESP8266_RTOS_SDK

5️⃣ Install ESP8266 Toolchain

Download Xtensa toolchain:

xtensa-lx106-elf

Extract it to:

D:\esp8266_toolchain


Toolchain binary path:

D:\esp8266_toolchain\xtensa-lx106-elf\bin

6️⃣ Python Setup

Install Python (example used here):

C:\Users\hprcse\AppData\Local\Programs\Python\Python313

7️⃣ Environment Variable Setup (IMPORTANT)

Run these commands inside MSYS2 MINGW32 shell
(or add them to ~/.bashrc for permanent setup)

# ESP8266 RTOS SDK path
export IDF_PATH=/c/msys32/home/hprcse/esp/ESP8266_RTOS_SDK

# Xtensa toolchain path
export PATH=/d/esp8266_toolchain/xtensa-lx106-elf/bin:$PATH

# Python path
export PATH="/c/Users/hprcse/AppData/Local/Programs/Python/Python313:$PATH"

Verify Setup
echo $IDF_PATH
which xtensa-lx106-elf-gcc
which python
python --version

8️⃣ Build the Project

Go to the example directory:

cd /d/github/esp8266-espnow-examples/espnow_SEND


Configure (first time only):

make menuconfig


Build:

make

9️⃣ Flash the ESP8266

Check COM port in Device Manager
Example: COM9

Flash command:

make flash ESPPORT=COM9


Monitor output:

make monitor ESPPORT=COM9


Exit monitor:

Ctrl + ]

🔟 Notes

Always use MSYS2 MINGW32 shell

Do NOT use PowerShell for building

ESP-NOW SEND and RECV must use same channel

Disable WiFi sleep if packets drop

📁 Examples Used (November – Week 1)

espnow_SEND

espnow_RECV

Source:

ESP8266_RTOS_SDK/examples/wifi/

