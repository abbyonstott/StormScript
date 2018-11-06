if [ -f ./*.stslib ]; then
    if [ ! -e ~/.stormscript ]; then
        mkdir ~/.stormscript
        echo 'export PATH=$PATH:'$HOME'/.stormscript' >> ~/.bashrc
        cp -r stormscript/ ~/.stormscript
    fi
    cp ./*.py ~/.stormscript
    cp ./*.stslib ~/.stormscript
    rm build.sh
else
    echo 'Error: not a library'
    rm build.sh
fi