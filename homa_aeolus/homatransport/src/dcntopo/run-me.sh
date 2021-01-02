EXP_NAME=$1
echo ../src -u Cmdenv -c InFileDist -r 0 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET config-${EXP_NAME}.ini
../src -u Cmdenv -c InFileDist -r 0 -n ..:../../simulations:../../../inet/examples:../../../inet/src -l ../../../inet/src/INET config-${EXP_NAME}.ini > output-${EXP_NAME}.log
