all:
	nasm -f bin ./bootloader/boot.asm -o ./bin/boot.bin
	nasm -f bin ./Kernel/empty_end.asm -o ./bin/empty_end.bin
	nasm -f elf ./Kernel/kernel_entry.asm -o ./bin/kernel_entry.o -i Kernel
	i386-elf-gcc -ffreestanding -m32 -g -c ./Kernel/kernel.cpp -o ./bin/kernel.o -I Kernel
	i386-elf-gcc -ffreestanding -m32 -g -c ./Drivers/vga.cpp -o ./bin/vga.o -I Drivers
	i386-elf-gcc -ffreestanding -m32 -g -c ./Drivers/port_io.cpp -o ./bin/port_io.o -I Drivers
	i386-elf-ld -o ./bin/kernel.bin -Ttext 0x1000 ./bin/kernel_entry.o ./bin/kernel.o ./bin/vga.o ./bin/port_io.o --oformat binary
	cat ./bin/boot.bin ./bin/kernel.bin > ./bin/short.bin
	cat ./bin/short.bin ./bin/empty_end.bin > ./bin/os.bin