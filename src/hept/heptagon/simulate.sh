#!/bin/bash
set -eE -o functrace
failure() {
  local lineno=$1
  local msg=$2
  echo "Failed at $lineno: $msg"
}
trap 'failure ${LINENO} "$BASH_COMMAND"' ERR

opam switch 4.03.0 > /dev/null
eval $(opam env)
# default values
node='display'
path='node.ept'
gui=true
prompt="Specify node with 's', path of the heptagon file with 'p' "
prompt+="and optionally -c 1 to run in non-gui mode.\nDefault is -s "
prompt+="display -p node.ept\n"
while getopts 's:p:k:c:h' flag
do
    case "${flag}" in
        s) node=${OPTARG} ;;
        p) path=${OPTARG} ;;
        k) compile_only=${OPTARG} ;;
        c) gui=false ;;
        h) printf "$prompt" ; exit 0 ;;
    esac
done
VERBOSE=1
if [[ -f "mc_ext.epi" ]]; then
heptc "mc_ext.epi"
fi

heptc -target c -s $node -hepts $path 
filename="${path##*/}";
filename="${filename%.*}"
filename="${filename,}"
if [[ -z "${filename}" ]]
then echo "Please enter a valid filepath!"; exit 0;
fi

if [[ -f "mc_ext_types.h" ]]; then
cp "mc_ext_types.h" $filename"_c/"
fi
if [[ -f "mc_ext.h" ]]; then
cp "mc_ext.h" $filename"_c/"
fi
if [[ -f "mc_ext.c" ]]; then
cp "mc_ext.c" $filename"_c/"
fi
cd $filename"_c/"

gcc -w -c -I $(heptc -where)/c *.c > /dev/null
# gcc -Wall -c -I $(heptc -where)/c _main.c  

# gcc -w -o $node *.o $(heptc -where)/c/math.o > /dev/null
gcc -w -o $node *.o > /dev/null

# echo "${node}"
# echo "${filename^}"
if [ ! -z "${compile_only}" ] ; then
  exit 0
fi

if [ "$gui" = true ] ; then
  cd ..
  hepts -mod "${filename^}" -node $node -exec $filename"_c/"$node
else
  # echo "Executing program in non-gui mode, enter inputs and press enter:"
  ./"$node"
fi
