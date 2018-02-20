#!/bin/bash
#sudo apt-get install mbw
for ((i=1;i<4096;i+=512))	##single core accesses (from 1MB up to 4GB)!
do
	mbw -n 4 $i -t2   # &   ##uncomment for dual core accesses
#	mbw -n 4 $i -t2 
done

#Post Scriptum: one can see that motherboard bus width is constant, and RAM
#memory bandwidth is divided amongs CPU cores. Obtain you RAM capabilities
#details with memtestx86+ bootable USB.
