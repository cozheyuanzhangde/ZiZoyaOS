## Important Things:
### Create a bootable CD-ROM ISO:
1. Bug fix - Initialize ax,ss,ds,es registers to 0
2. Bug fix - Change KERNEL_OFFSET from 0x1000 to 0x7e00
3. Use linux dd: dd if=/dev/zero of=zizoyaos.img bs=1024 count=1440 - Create a 1.44MB floppy disk image file
4. Use linux dd: dd if=ZizoyaOS.bin of=zizoyaos.img conv=notrunc - write the binary file to the image
5. Use fdtoiso under /tools to create the CD-ROM ISO.
6. Finally burn the ISO into the CD and boot it on a REAL PC.