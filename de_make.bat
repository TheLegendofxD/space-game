@echo off

title Gameboy C Compiler de_build
echo Gameboy C Compiler de_build

c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o builds\data\de_build.o de_build.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o builds\de_build.gb builds\data\de_build.o

PAUSE
start builds\de_build.gb