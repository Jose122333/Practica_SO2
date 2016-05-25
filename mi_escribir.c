#include <stdio.h>
#include <string.h>
#include "bloques.h"
#include "directorios.h"

/* 
* Simeon Yordanov Grancharov
* Jose Antonio Vela Martín
*/

int main(int argc, char **argv){
	//We declare all the necessary variables
	int descriptor,bytesEscritos,offset,size;
	if(argc<4){
		printf("Syntax error, not enough argumentes, file mi_escribir.c\n"
			"Correct Order:\n"
			"Argument 1: File System Name\n"
			"Argument 2: path\n"
			"Argument 3: offset\n");
		return -1;
	}
	//We open the file system
	descriptor = bmount(argv[1]);
	if(descriptor<0){
		printf("Error while openinigkd the file system, file mi_escribir.c\n");
		return -1;
	}
	bytesEscritos = 0;
	//We save the file in the 
	unsigned char input[3000];
	strcpy(input,"BRANThe morning had dawned clear and cold, with a crispness that hinted at the end of summer. They set forth at daybreak to see a man beheaded, twenty in all, and Bran rode among them, nervous with excitement. This was the first time he had been deemed old enough to go with his lord father and his brothers to see the king’s justice done. It was the ninth year of summer, and the seventh of Bran’s life.The man had been taken outside a small holdfast in the hills. Robb thought he was a wildling, his sword sworn to Mance Rayder, the King-beyond-the-Wall. It made Bran’s skin prickle to think of it. He remembered the hearth tales Old Nan told them. The wildlings were cruel men, she said, slavers and slayers and thieves. They consorted with giants and ghouls, stole girl children in the dead of night, and drank blood from polished horns. And their women lay with the Others in the Long Night to sire terrible half- human children.But the man they found bound hand and foot to the holdfast wall awaiting the king’s justice was old and scrawny, not much taller than Robb. He had lost both ears and a finger to frostbite, and he dressed all in black, the same as a brother of the Night’s Watch, except that his furs were ragged and greasy.The breath of man and horse mingled, steaming, in the cold morning air as his lord father had the man cut down from the wall and dragged before them. Robb and Jon sat tall and still on their horses, with Bran between them on his pony, trying to seem older than seven, trying to pretend that he’d seen all this before.A faint wind blew through the holdfast gate. Over their heads flapped the banner of the Starks of Winterfell: a grey direwolf racing across an ice-white field.Bran’s father sat solemnly on his horse, long brown hair stirring in the wind. His closely trimmed beard was shot with white, making him look older than his thirty-five years. He had a grim cast to his grey eyes this day, and he seemed not at all the man who would sit before the fire in the evening and talk softly of the age of heroes and the children of the forest. He had taken off Father’s face, Bran thought, and donned the face of Lord Stark of Winterfell.");
	size = strlen(input);
	offset = atoi(argv[3]);
	printf("El offset es %d\n",offset);
	bytesEscritos = mi_write(argv[2],input,offset,size);
	if(bytesEscritos<0){
		printf("Error in mi_write function, file mi_escribir.c\n");
		return -1;
	}
	printf("The number of bytes written is: %d\n", bytesEscritos);
	//We close the file system
	if(bumount(descriptor)<0){
		printf("Error while closing the file system, file mi_escribir.c\n");
		return -1;
	}
	return 0;
}