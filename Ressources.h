/*
 * ressources.h
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */

#ifndef RESSOURCES_H_
#define RESSOURCES_H_
#include "List.h"

typelist(mesh, Mesh*);
typelist(shader, Shader*);
typelist(texture, Texture*);

typedef struct Ressources_s{
	char* name; //Nom de l'objet
	list_mesh* mesh; //Tableau contenant les diff�rents meshs
	list_shader* shader; //Tableau contenant les diff�rents shaders
	list_texture* texture;//Tableau contenant les diff�rentes textures
} Ressources_s;


void ressources_init();
void ressources_load();

#endif /* RESSOURCES_H_ */
