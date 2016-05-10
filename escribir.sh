#script
#!/bin/bash
# $1 --> Disco virtual

#creamos el sistema de ficheros

rm $1
make
clear
echo
echo MI_MKFS -------------------------------------------
echo creamos el sistema de ficheros con 100000 bloques
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_mkfs $1 100000
#creamos un fichero en el directorio raiz
echo
echo MI_MKDIR -------------------------------------------
echo creamos un fichero en la raiz
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_mkdir $1 7 /fichero.txt
#intentamos crear un fichero dentro de otro
echo
echo MI_MKDIR -------------------------------------------
echo intentamos crear un fichero dentro de otro
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_mkdir $1 7 /fichero.txt/fichero2.txt
#listamos la raiz para ver el fichero
echo
echo MI_LS -------------------------------------------
echo listamos la raiz para ver el fichero creado
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_ls $1 /
#escribimos en el fichero creado(offset 0)
echo
echo MI_ESCRIBIR -------------------------------------------
echo escribimos en el fichero creado en el offset 0
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_escribir $1 /fichero.txt 0
echo
#leemos el fichero creado(offset 0)
echo MI_CAT -------------------------------------------
echo leemos en el fichero creado en el offset 0
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_cat $1 /fichero.txt > prueba0.txt
#escribimos en el fichero creado(offset 5120)
echo
echo MI_ESCRIBIR -------------------------------------------
echo escribimos en el fichero creado en el offset 5120
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_escribir $1 /fichero.txt 5120
#leemos el fichero creado(offset 5120)
echo MI_CAT -------------------------------------------
echo leemos en el fichero creado en el offset 5120
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_cat $1 /fichero.txt > prueba5120.txt
#escribimos en el fichero creado(offset 256000)
echo
echo MI_ESCRIBIR -------------------------------------------
echo escribimos en el fichero creado en el offset 256000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_escribir $1 /fichero.txt 256000
#leemos el fichero creado(offset 256000)
echo MI_CAT -------------------------------------------
echo leemos en el fichero creado en el offset 256000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_cat $1 /fichero.txt > prueba256000.txt
#escribimos en el fichero creado(offset 30720000)
echo
echo MI_ESCRIBIR -------------------------------------------
echo escribimos en el fichero creado en el offset 30720000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_escribir $1 /fichero.txt 30720000
#leemos el fichero creado(offset 30720000)
echo MI_CAT -------------------------------------------
echo leemos en el fichero creado en el offset 30720000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_cat $1 /fichero.txt > prueba30720000.txt
#escribimos en el fichero creado(offset 71680000)
echo
echo MI_ESCRIBIR -------------------------------------------
echo escribimos en el fichero creado en el offset 71680000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_escribir $1 /fichero.txt 71680000
#leemos el fichero creado(offset 71680000)
echo MI_CAT -------------------------------------------
echo leemos en el fichero creado en el offset 71680000
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo
./mi_cat $1 /fichero.txt > prueba71680000.txt
