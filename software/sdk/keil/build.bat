set path=D:\Keil_v5\ARM\ARMCC\bin
fromelf.exe --bin -o ./Output/gek1109_demo.bin ./Objects/gek1109_demo.axf
fromelf.exe -rc -o ./Output/gek1109_demo.asm ./Objects/gek1109_demo.axf
fromelf.exe -ad -o ./Output/gek1109_demo.data ./Objects/gek1109_demo.axf
fromelf.exe -cvf ./Objects/gek1109_demo.axf --vhx --32x1 -o ./Output/gek1109.hex
fromelf.exe -cvf ./Objects/gek1109_demo.axf -o ./Output/gek1109_asm.txt


