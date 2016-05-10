#script
#!/bin/bash
# $1 --> Disco virtual

#Montamos el sistema de ficheros

rm $1
make
clear
echo
echo --------MI_MIKFS-------------
echo creamos el sistema de ficheros con 100000 bloques
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_mkfs $1 100000

#Crear carpetas y ficheros
echo ┌──────────────────────────────────────────────────┐
echo │./mi_mkdir $1 7 "/dirA0/"                         
echo │./mi_mkdir $1 7 "/dirA0/A.dat"                    
echo │./mi_mkdir $1 7 "/dirB0/"                         
echo │./mi_mkdir $1 7 "/dirC0/"                         
echo │./mi_mkdir $1 7 "/dirD0/"                         
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s

./mi_mkdir $1 7 "/dirA0/"
./mi_mkdir $1 7 "/dirA0/A.dat"
./mi_mkdir $1 7 "/dirB0/"
./mi_mkdir $1 7 "/dirC0/"
./mi_mkdir $1 7 "/dirD0/"

echo ┌───────────────────────────────────────────────────┐
echo │./mi_escribir $1 "/dirA0/A.dat"                    
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_escribir $1 "/dirA0/A.dat" 0

#Comprobar la informacion actual del fichero A.dat
echo ┌───────────────────────────────────────────────────┐
echo │Ejecutando ./mi_stat $1 "/dirA0/A.dat"             
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_stat $1 "/dirA0/A.dat"

echo ┌───────────────────────────────────────────────────┐
echo │Ejecutando ./mi_cat $1 "/dirA0/A.dat"              
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat $1 "/dirA0/A.dat"
echo -------------------------------------------


echo ┌───────────────────────────────────────────────────┐
echo │Ejecutando ./mi_ln $1 "/dirA0/A.dat" "/dirB0/B.dat"
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_ln $1 "/dirA0/A.dat" "/dirB0/B.dat"

echo ┌───────────────────────────────────────────────────┐
echo │Ejecutando ./mi_ln $1 "/dirA0/A.dat" "/dirC0/C.dat"
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_ln $1 "/dirA0/A.dat" "/dirC0/C.dat"

echo ┌───────────────────────────────────────────────────┐
echo │Ejecutando ./mi_ln $1 "/dirA0/A.dat" "/dirD0/D.dat"
echo └───────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_ln $1 "/dirA0/A.dat" "/dirD0/D.dat"
echo -------------------------------------------


echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_stat $1 "/dirA0/A.dat"            
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_stat $1 "/dirA0/A.dat"


echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_cat $1  "/dirB0/B.dat"            
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat $1 "/dirB0/B.dat"
echo

echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_cat $1 "/dirC0/C.dat"             
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat $1 "/dirC0/C.dat"

echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_cat $1 "/dirD0/D.dat"             
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat $1 "/dirD0/D.dat"
echo -------------------------------------------

echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_rm $1  "/dirB0/B.dat"		
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_rm $1 "/dirB0/B.dat"
echo

echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_rm $1 "/dirC0/C.dat"		
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_rm $1 "/dirC0/C.dat"
echo

echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_rm $1 "/dirD0/D.dat"		
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_rm $1 "/dirD0/D.dat"


echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_stat $1 "/dirA0/A.dat"		
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_stat $1 "/dirA0/A.dat"
echo

echo
echo ┌──────────────────────────────────────────────────┐
echo │Ejecutando ./mi_rm $1 "/dirA0/A.dat"		
echo └──────────────────────────────────────────────────┘
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_rm $1 "/dirA0/A.dat"


