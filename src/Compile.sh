#/bin/sh

# Simple compile script by Immortal

make clean
make RELEASE=1
mv -v libEThax.so ./EThax_Bin/libEThax.so
mv -v ETmix.pk3 ./EThax_Bin/ETmix.pk3
make clean

echo "EThax-Private its Ready to Kick Ass :)"
