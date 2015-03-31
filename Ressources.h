/*
 * ressources.h
 *
 *  Created on: 30 mars 2015
 *      Author: ethel
 */

#ifndef RESSOURCES_H_
#define RESSOURCES_H_
#include "List.h"
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"


typelist(mesh, Mesh*);
typelist(shader, Shader*);
typelist(texture, Texture*);

typedef struct Ressources{
	char* name; //Nom de l'objet
	list_mesh* meshes; //Tableau contenant les diff�rents meshs
	list_shader* shaders; //Tableau contenant les diff�rents shaders
	list_texture* textures;//Tableau contenant les diff�rentes textures
} Ressources;

Ressources Ressource;


void ressources_init();
void ressources_load();
Shader* get_Shaderfromlist(int a);
Mesh* get_MeshfromList(int a);
Texture* get_TexturefromList(int a);

#endif /* RESSOURCES_H_ */
