#                           hello! world!                               
########################################################################
#--------> File Name:1.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-08-15 17:40:44
########################################################################
#!/bin/bash
A=B
echo "PID for 1.sh before exec/source/fork:$$"
export A
echo "1.sh : \$A is $A"
case $1 in 
    exec)
        echo "using exec..."
        exec ./2.sh ;;
    source)
        echo "using sourcer..."
        . ./2.sh ;;
    *)
        echo "using fork by default..."
        ./2.sh ;;
esac
echo "PID for 1.sh after exer/source/fork:$$"
echo "1.sh \$A is $A"


