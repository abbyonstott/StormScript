#!/bin/bash
if [ `whoami` == 'root' ]; then
    sudo cp bin/sts /usr/bin
    cmd1='export PATH='
    cmd2='/libs:$PATH'
    cmd=$cmd1`pwd`$cmd2
    echo $cmd >> ~/.bashrc
    echo test: `sts example/helloworld.sts`
else
    echo Please run again as root
fi