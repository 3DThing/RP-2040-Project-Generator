import os
from sys import platform

osstr = platform

print("This is an automatic installer: Project Generator RP2040")
start = input("Do you want to continue? y/n: ")
if start == "y" or start == "Y":
    gccarm = input("Do you want install GCC-ARM y/n: ")
    if gccarm == "y" or start == "Y":
        os.system("sudo apt install cmake gcc-arm-none-eabi libnewlib-arm-none-eabi libstdc++-arm-none-eabi-newlib git")
    picosdk = input("Do you want install PicoSDK C++ y/n: ")
    if picosdk == "y" or start == "Y":
        os.system("mkdir ~/pico")
        os.system("git clone https://github.com/raspberrypi/pico-sdk")
        os.system("mv pico-sdk ~/pico")
        picosdk = input("Do you want install Project Generator y/n: ")
    if picosdk == "y" or start == "Y":
        os.system("mkdir ~/pico")
        os.system("git clone https://github.com/3DThing/RP-2040ProjectGenerator")
        os.system("mv RP-2040ProjectGenerator/Bin/RP2040-projectgenerator_linux  ~/pico/")
        os.system("mv RP-2040ProjectGenerator/Bin/lib ~/pico/")
        os.system("rm -R RP-2040ProjectGenerator")
else:
    print("Goodby")
