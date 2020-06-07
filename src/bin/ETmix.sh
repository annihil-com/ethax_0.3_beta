#!/bin/sh
#---------------------------
#export EThax_CONF_FILE=ETconf
#export EThax_LOG_FILE=EThaxLog
#log work only with make DEBUG=1
#export EThax_PBSS=clean
#export CLGUID=23kj45mj6i8jfurk87nfju76rj98dk66


# explanaition of shortcuts
#    [c] - current spree count
#    [v] - victim name
#    [n] - clean victim name
#    [t] - total kills
#    [m] - double/triple/multikill msg
#    [x]    - Player XP
#    [p] - Player name
#    [M] - Mod name
#    [h] - Player health
#    [k] - Killer name
#    [K] - Clean killer name
#    [q] - amount of punkbuster screenshots requested
#---------------------------


export LD_PRELOAD=/home/user name/EThax-0.2_Final/src/EThax_Src/EThax_Bin/libEThax.so 
./et.x86 +set net_port $(dd if=/dev/urandom count=1 2> /dev/null | cksum | cut -f1 -d" ") $*
unset LD_PRELOAD
exit 0


#export LD_PRELOAD=home/user name/EThax-0.2_Final/src/EThax_Src/EThax_Bin/libEThax.so 
#"home/user name/et-sdl-sound" +set fs_basepath "home/user name/enemy-territory/" $*
#unset LD_PRELOAD
#exit 0

#vote kick by pass mod by alexplay :)
#+set net_port $(dd if=/dev/urandom count=1 2> /dev/null | cksum | cut -f1 -d" ") $* 
