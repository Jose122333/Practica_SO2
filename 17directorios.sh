#script
#!/bin/bash
# $1 --> Disco virtual
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
#comprobamos que al crear 17 subdirectorios los bloques de datos del padre son 2, y que al eliminar un subdirectorio el directorio padre tiene 1 bloque de datos
echo
echo MI_MKDIR -------------------------------------------
echo creamos un directorio llamado d1 en la raiz con 17 subdirectorios sd1, sd2..., sd17
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
echo
./mi_mkdir $1 7 /d1/
for i in $(seq 1 17)
do
	./mi_mkdir $1 7 /d1/sd$i/
done
echo
echo MI_STAT -------------------------------------------
echo mostramos la metainformacion del directorio para ver que tiene 2 bloques de datos
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_stat $1 /d1/
echo
echo MI_LS -------------------------------------------
echo listamos el directorio para ver sus subdirectorios
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_ls $1 /d1/
echo
echo MI_RM -------------------------------------------
echo eliminamos el subdirectorio sd17 de d1
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_rm $1 /d1/sd17/
echo
echo MI_STAT -------------------------------------------
echo mostramos la metainformacion de d1 para ver que tiene 1 bloque de datos
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_stat $1 /d1/
echo
echo MI_LS -------------------------------------------
echo volvemos a listar el directorio para ver que se ha eliminado un subdirectorio
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_ls $1 /d1/
echo
echo MI_MKDIR -------------------------------------------
echo creamos un fichero en /d1/file1.txt
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_mkdir $1 7 /d1/file1.txt
echo
echo MI_LS -------------------------------------------
echo volvemos a listar el directorio para ver que se ha creado el fichero
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_ls $1 /d1/
echo
echo MI_MKDIR -------------------------------------------
echo intentamos crear un directorio en el fichero en file1.txt
echo Deberia dar error
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_mkdir $1 7 /d1/file1.txt/dir22/
echo
echo MI_MKDIR -------------------------------------------
echo intentamos crear un fichero en el fichero en file1.txt
echo Deberia dar error
echo
echo Pulse cualquier tecla para continuar...
read -n 1 -s
echo ----------------------------------------------------
./mi_mkdir $1 7 /d1/file1.txt/file2.txt
