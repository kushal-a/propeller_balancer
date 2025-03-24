#!/usr/bin/env bash
cd "heptagon/"
(./simulate.sh -s main -p $1.ept -k 1) 

cd ".."

dest_src=$pwd."/supervisor"
src=$pwd."/heptagon/$1_c"

cp "$src/$1_types.c" "$dest_src/$1_types.cpp"
cp "$src/$1_types.h" "$dest_src/$1_types.h"
cp "$src/$1.c" "$dest_src/$1.cpp"
cp "$src/$1.h" "$dest_src/$1.h"

cp "$src/mc_ext.c" "$dest_src/mc_ext.cpp"
cp "$src/mc_ext.h" "$dest_src/mc_ext.h"
cp "$src/mc_ext_types.h" "$dest_src/mc_ext_types.h"

sed -i 's/int/long/g' "$dest_src/$1.cpp"
sed -i 's/int/long/g' "$dest_src/$1.h"
sed -i 's/int/long/g' "$dest_src/$1_types.h"
sed -i 's/int/long/g' "$dest_src/mc_ext.cpp"
sed -i 's/int/long/g' "$dest_src/mc_ext.h"
sed -i 's/int/long/g' "$dest_src/mc_ext_types.h"

# uncommented the below line
sed --in-place '/pervasives.h/d' "$dest_src/propeller_balancer_types.h"

