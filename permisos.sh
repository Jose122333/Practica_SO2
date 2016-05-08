#! /bin/bash

clear
rm disco
make
clear
./mi_mkfs disco 10000

echo Script de comprobación de escritura \(mi_escribir.c\), lectura \(mi_cat.c\) y cambio de permisos \(mi_chmod.c\)
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------

echo Creamos un archivo en el directorio raíz, llamado quijote.txt, con todos los permisos \(.\/mi_mkdir disco \/quijote.txt\).
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_mkdir disco 7 /quijote.txt
echo ----------------------------------------------------

echo Escribimos en el fichero un fragmento de El Quijote. El texto a escribir se encuentra dentro del código de escribir.c, y escribiremos de forma que se usen punteros indirectos, con un offset de 50000 \(.\/mi_escribir disco \/quijote.txt 50000\)
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_escribir disco /quijote.txt 50000
echo ----------------------------------------------------

echo A continuación, leeremos el fichero \(\/mi_cat disco \/quijote.txt\)
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat disco /quijote.txt
echo ----------------------------------------------------

echo Vamos a cambiar los permisos del fichero. Le quitaremos el permiso de lectura y escritura, por ejemplo asignando el permiso 1 \(--x\) \(.\/mi_chmod disco 1 \/quijote.txt\)
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_chmod disco 1 /quijote.txt
echo ----------------------------------------------------

echo Intentamos leer el archivo. Debería mostrar error.
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_cat disco /quijote.txt
echo ----------------------------------------------------

echo Intentamos escribir de nuevo en el archivo. También debería mostrar error.
echo Pulse cualquier tecla para continuar...
read -n 1 -s
./mi_escribir disco /quijote.txt 0
echo ----------------------------------------------------

echo Script finalizado.

