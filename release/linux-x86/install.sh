#!/bin/bash
if [ `whoami` == 'root' ]; then
    sudo cp bin/sts /usr/bin
    cmd1='export PATH='
    cmd2='/libs:$PATH'
    cmd=$cmd1`pwd`$cmd2
    echo $cmd >> ~/.bashrc
    echo test: `sts example/helloworld.sts`
    if [ `sts example/helloworld.sts` == 'Hello, World!' ]; then
        echo "Test: Test Successful"
        echo Restart terminal for some changes to take place
    else
        echo Error: did not install correctly, expected output of Hello, World! Got `sts example/helloworld.sts` instead.
    fi
else
    echo Please run again as root
fi