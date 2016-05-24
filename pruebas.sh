#script
     #!/bin/bash
     # $1 --> Disco virtual
      #$2 --> Directorio de la simulacion (/simul_aaaammddhhmmss/).

     #listamos la raiz
     clear
   echo MI_LS -------------------------------------------
   echo Listamos el directorio raíz
   read -n 1 -s
   echo
   ./mi_ls $1 /

     #cambiamos permisos al directorio de la simulacion
   echo
   echo MI_CHMOD -------------------------------------------
   echo Cambiamos permisos al directorio de la simulacion $2
   read -n 1 -s
   echo
   ./mi_chmod $1 1 $2
     #volvemos a listar para ver los permisos del directorio de simulacion


   echo
   echo MI_LS -------------------------------------------
   echo Volvemos a listar para ver los permisos del directorio de la simulacion
   read -n 1 -s
   echo
   ./mi_ls $1 /
     #volvemos a cambiar los permisos del directorio de simulacion
   echo
   echo MI_CHMOD -------------------------------------------
   echo Volvemos a cambiar los permisos del directorio de la simulacion
   read -n 1 -s
   echo
   ./mi_chmod $1 7 $2

     #listamos de nuevo la raiz
   echo
   echo MI_LS -------------------------------------------
   echo Listamos de nuevo la raíz
   read -n 1 -s
   echo
   ./mi_ls $1 /

     #listamos el directorio de simulacion
   echo
   echo MI_LS -------------------------------------------
   echo Listamos el directorio de la simulacion
   read -n 1 -s
   echo
   ./mi_ls $1 $2

     #hacemos un mi_cat de informe.txt que ha generado el verificador de la simulacion
   echo
   echo MI_CAT -------------------------------------------
   echo Hacemos un mi_cat del informe.txt al fichero output.txt para ver que coinciden los tamaños
   read -n 1 -s
   echo
   ./mi_cat $1 ${2}informe.txt > output.txt

     #creamos un enlace dentro del directorio raiz que apunta al informe.txt
   echo
   echo MI_LN -------------------------------------------
   echo Creamos un enlace dentro del directorio raíz que apunta a informe.txt
   read -n 1 -s
   echo
   ./mi_ln $1 ${2}informe.txt /enlace

     #hacemos un mi_stat del informe.txt para ver como nlinks ahora vale 2
   echo
   echo MI_STAT -------------------------------------------
   echo Hacemos un mi_stat del informe.txt para ver como nlinks vale 2
   read -n 1 -s
   echo 
./mi_stat $1 ${2}informe.txt
 
#listamos la raiz para ver el enlace creado
echo
echo MI_LS -------------------------------------------
echo Listamos la raíz para ver el enlace creado
read -n 1 -s
echo
./mi_ls $1 /
 
#borramos el enlace
echo
echo MI_RM -------------------------------------------
echo Borramos este enlace
read -n 1 -s
echo
./mi_rm $1 /enlace
 
#volvemos a hacer stat de informe.txt para ver como nlinks vale 1 
echo
echo MI_STAT -------------------------------------------
echo Volvemos a hacer un stat del informe.txt para ver como ha cambiado nlinks a 1
read -n 1 -s
echo
./mi_stat $1 ${2}informe.txt
 
#listamos otra vez para ver que enlace ha sido borrado
echo
echo MI_LS -------------------------------------------
echo  Listamos la raíz para ver que enlace ya no está
read -n 1 -s
echo
./mi_ls $1 /
 
#llamamos a leer_SF que muestra la informacion del SB, MB y AI
echo 
echo leer_sf -------------------------------------------
echo Llamamos a leer_sf para mostrar toda la informacion
read -n 1 -s
echo
./leer_sf $1
      