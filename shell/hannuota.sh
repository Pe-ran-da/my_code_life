#                           hello! world!                               
########################################################################
#--------> File Name:hannuota.sh
#--------> Version: 1.0
#--------> Author: Peranda
#--------> Mail: 
#--------> Created Time:2018-09-08 21:26:45
########################################################################
#!/bin/bash

E_NOPARAM=66
E_BADPARAM=67
Moves=

dohanoi() {
    case $1 in 
        0)
            ;;
        *)
            dohanoi "$(( $1 - 1 ))" $2 $3 $4
            echo move $2 "-->" $3
        let "Moves += 1"
            dohanoi "$(( $1 - 1 ))" $2 $3 $4
            ;;
    esac
}

case $# in 
1)
    case $(( $1 > 0 )) in 
    1)
        dohanoi $1 1 3 2
        echo "Total moves = $Moves"
        exit 0;
        ;;
    *)
        echo "$0 : illegal value  for number of disks";
        exit $E_BADPARAM;
        ;;
    esac 
    ;;
*)
    echo "usage: $0 N"
    echo "       Where \"N\" is the number of disks."
    exit $E_NOPARAM;
    ;;
esac

