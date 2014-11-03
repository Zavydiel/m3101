gcc -shared -fPIC -o lib.so ../tp3/fct.c
LD_PRELOAD=./lib.so ls -a
