#!/bin/tcsh

@ N=$1 + 1
set A = `head -$N finished.dat| tail -1`
echo $A
@ B=-1

./adc $A $B
#./tdc3 $A $B

#./tof1 $A $B
#./tdc2 $A $B
#./tof2 $A $B
#./tof3 $A $B
#root -b -q -l step4_sectoroffset.C\($A\)
#./tof4 $A $B
#./tof5 $A $B

exit
