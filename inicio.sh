#!/bin/bash
FILE=$1

if [ -f $FILE ];
then
   rm $FILE
   make clean
   make
   ./my_mkfs $FILE 100000
   ./leer_SF $FILE
   ./escribir $FILE
   ./leer_SF $FILE      
   make clean
else
   make clean
   make
   ./my_mkfs $FILE 100000
   ./leer_SF $FILE
   ./escribir $FILE
   ./leer_SF $FILE 
   make clean
fi
