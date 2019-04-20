#!/bin/bash
cmake .
make -j $(nproc)
sudo mv stormscript /usr/bin/stormscript

sudo cp src/core/errors.sts /usr/bin
sudo cp src/core/live.sts /usr/bin
sudo chmod 777 /usr/bin/errors.sts
sudo chmod 777 /usr/bin/live.sts