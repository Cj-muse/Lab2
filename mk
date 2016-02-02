#!/bin/bash
VFD=FDimage

as86 -o ts.o ts.s
bcc  -c -ansi t.c
bcc  -c -ansi io.c
ld86 -d -o mtx ts.o t.o io.o mtxlib /usr/lib/bcc/libc.a

echo mount $VFD on mnt
sudo mount  FDimage mnt
#sudo mount -o loop FDimage mnt

rm mnt/boot/*

cp mtx mnt/boot
umount mnt

echo ready to go?
read dummy

qemu-system-x86_64 -fda FDimage -no-fd-bootchk

