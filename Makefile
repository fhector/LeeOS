CC=arm-elf-gcc
LD=arm-elf-ld
OBJCOPY=arm-elf-objcopy
CFLAGS= -O2 -g
ASFLAGS= -O2 -g
LDFLAGS=-Thelloworld.lds -Ttext 00000000

OBJS=start.o helloworld.o

.c.o:
	$(CC) $(CFLAGS) -c $<
.s.o:
	$(CC) $(ASFLAGS) -c $<

helloworld:$(OBJS)
	$(CC) -static -nostartfiles -nostdlib $(LDFLAGS) $? -o $@ -lgcc
	$(OBJCOPY) -O binary $@ helloworld.bin
clean:
	rm *.o helloworld helloworld.bin -f


