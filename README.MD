#Copyright (C) 2009  david leels <davidontech@gmail.com>
############################################################
1.install CrossTools
	sudo cp /where/your/compiler/locate/leeos_tools_for_linux.tart.gz /usr
	cd /usr
	sudo tar zxvf leeos_tools_for_linux.tar.gz	
	sudo echo "PATH=$PATH:/usr/leeos_tools_for_linux/bin"  >> etc/profile
############################################################
2.install SkyEye

	tar jxvf skyeye-1.2.6_rc1.tar.bz2
	cd skyeye-1.2.6_rc1
	./configure
	make
	sudo make install
############################################################
3.

Skyeye.conf


cpu: arm920t
mach: s3c2410c
mem_bank: map=M, type=RW, addr=0x30000000, size=0x00800000, file=./leeos.bin,boot=yes
mem_bank: map=I, type=RW, addr=0x48000000, size=0x20000000