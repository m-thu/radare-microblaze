#!/bin/sh
# http://www.wiki.xilinx.com/QEMU
TARGET=microblazeel-elf
PREFIX=~/${TARGET}

HOME=$(pwd)
mkdir -p $PREFIX
cd $PREFIX

git clone git://github.com/Xilinx/qemu.git
cd qemu
git submodule update --init pixman dtc
# Python 3 isn't supported!
./configure --prefix=${PREFIX} --target-list="microblazeel-softmmu" --enable-fdt --disable-kvm --python=$(which python2) --disable-werror
make -j$(nproc)
make install

cd $HOME
