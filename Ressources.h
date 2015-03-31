/*
 * ressources.h
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */

#ifndef RESSOURCES_H_
#define RESSOURCES_H_
#include "List.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include <stdio.h>



typelist(mesh, Mesh*);
typelist(shader, Shader*);
typelist(texture, Texture*);

typedef struct Ressources_s{
	list_mesh* meshes; //Tableau contenant les diff�rents meshs
	list_shader* shaders; //Tableau contenant les diff�rents shaders
	list_texture* textures;//Tableau contenant les diff�rentes textures
} Ressources_s;

Ressources_s Ressource;

void ressources_init();
void ressources_load();

#endif /* RESSOURCES_H_ */
