#!/bin/bash
tresh="0.2"
loadPC=(`cat /proc/loadavg`); echo "host loadvg: "${loadPC[2]}" (treshold=$tresh)"
echo "=========================================================="
echo "checking servers loads:"
SERVERS=("localhost" "192.168.0.11")
for SERVER in "${SERVERS[@]}"
do
    loadPC=(`ssh lenarczp@$SERVER 'cat /proc/loadavg'`)
    echo "[ $SERVER ] loadavg: "${loadPC[2]}
    if (( `echo "${loadPC[2]} < $tresh" | bc -l` == 1 ))
    then
        echo "[ $SERVER ] shutdown now"
    fi
    echo "----------------------------------------------------------"
done
echo "...done"
echo "=========================================================="
