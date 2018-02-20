#!/bin/bash
#sudo apt-get install mbw
for ((i=512;i<4096;i+=512))	##single core accesses!
do
	mbw -n 1 $i # &   ##uncomment for dual core accesses
#	mbw -n 1 $i 
done

#Post Scriptum: one can see that motherboard bus width is constant, and RAM
#memory bandwidth is divided amongs CPU cores.
