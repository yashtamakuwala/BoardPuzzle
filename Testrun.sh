#!/bin/sh
 PROG=./puzzle

 case $1 in
 1) T=Tests/bad* ;;
 2) T=Tests/sol* ;;
 3) T=Tests/unsol* ;;
 esac

 if [ A$T != A ]
 then
    for i in $T
    do
    echo =================  $i  ==================
    $PROG < $i
    done
 else
    echo Usage $0 "[1|2|3]"
 fi