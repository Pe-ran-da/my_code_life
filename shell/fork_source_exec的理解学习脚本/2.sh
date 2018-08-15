#                           hello! world!                               
########################################################################
#--------> File Name:2.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-15 17:49:46
########################################################################
#!/bin/bash
echo "PID for 2.sh $$"
echo "2.sh get \$A=$A from 1.sh"
A=C
export A
echo "2.sh: \$A is $A"
