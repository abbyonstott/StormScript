if [ -f ./*.stslib ]; then
    if [ ! -e ~/.stormscript ]; then
        mkdir ~/.stormscript
        echo 'export PATH=$PATH:'$HOME'/.stormscript' >> ~/.bashrc
        cp -r stormscript/ ~/.stormscript
    fi
    cp ./*.py ~/.stormscript
    cp ./*.stslib ~/.stormscript
else
    echo 'Error: not a library'
fi