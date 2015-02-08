/*
 * Mesh.h
 *
 *  Created on: 5 f�vr. 2015
 *      Author: Gabriel
 */

#ifndef MESH_H_
#define MESH_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	float* vertices;
	float* normals;
	int* triangles;
	int* normals_id;
	int v,vn,f;
} Mesh;

int mesh_load_from_obj(Mesh* mesh, char* filename);

void mesh_send_to_shader(Mesh* mesh);

float* mesh_get_vertices(Mesh* mesh);

float* mesh_get_normals(Mesh* mesh);

void mesh_free(Mesh* mesh);

#endif /* MESH_H_ */
