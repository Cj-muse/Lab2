#!/bin/bash
#VFD=FDimage
as86 -o ts.o ts.s
bcc  -c -ansi t.c
bcc  -c -ansi io.c
ld86 -d -o mtx ts.o t.o io.o mtxlib /usr/lib/bcc/libc.a

echo mount mtximage on mnt
sudo mount -o loop mtximage mnt
#echo mount $VFD on mnt
#sudo mount VFD mnt
#sudo mount -o loop FDimage mnt

sudo rm mnt/boot/*

sudo cp mtx mnt/boot
sudo umount mnt

echo ready to go?
read dummy

qemu-system-x86_64 -fda mtximage -no-fd-bootchk

