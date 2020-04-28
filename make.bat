@echo off

title Gameboy C Compiler
echo Gameboy C Compiler

c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -c -o builds\data\main.o main.c
c:\gbdk\bin\lcc -Wa-l -Wl-m -Wl-j -DUSE_SFR_FOR_REG -o builds\imutes_spaceshooter.gb builds\data\main.o

PAUSE
start builds\imutes_spaceshooter.gb