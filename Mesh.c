/*
 * Mesh.c
 *
 *  Created on: 7 f�vr. 2015
 *      Author: Gabriel
 */

#include "Mesh.h"


int mesh_load_from_obj(Mesh* mesh, char* filename) {

	FILE* file = fopen(filename, "r");
	char buf[80];
	int v=0, vn=0, f=0, i=0, res=0;


	if(!file) {
		printf("Cannot open .obj file : %s", filename);
		return 0;
	}

	//Count the vertices (v), the normals (vn) and the triangles (f)
	while(res!=-1) {
		res = fscanf(file, "%s", buf);
		if(strcmp("v", buf)==0) {
			v++;
		}
		if(strcmp("vn", buf)==0) {
			vn++;
		}
		if(strcmp("f", buf)==0) {
			f++;
		}
	}
	mesh->v=v;
	mesh->vn=vn;
	mesh->f=f;
	mesh->vertices = calloc(3*v, sizeof(float));
	mesh->normals = calloc(3*vn, sizeof(float));
	mesh->triangles = calloc(3*f, sizeof(int));
	mesh->normals_id = calloc(3*f, sizeof(int));

	rewind(file);
	res=0;
	while(res!=-1) {
			res = fscanf(file, "%s", buf);
			if(strcmp("v", buf)==0) {
				fscanf(file, "%f %f %f\n",
								&(mesh->vertices[i*3]),
								&(mesh->vertices[i*3+1]),
								&(mesh->vertices[i*3+2]));
				i++;
				if(i==v) i=0;
			}
			if(strcmp("vn", buf)==0) {
				fscanf(file, "%f %f %f\n",
								&(mesh->normals[i*3]),
								&(mesh->normals[i*3+1]),
								&(mesh->normals[i*3+2]));
				i++;
				if(i==vn) i=0;
			}
			if(strcmp("f", buf)==0) {
				fscanf(file, "%d//%d %d//%d %d//%d\n",
								&(mesh->triangles[i*3]),&(mesh->normals_id[i*3]),
								&(mesh->triangles[i*3+1]),&(mesh->normals_id[i*3+1]),
								&(mesh->triangles[i*3+2]),&(mesh->normals_id[i*3+2]));
				i++;
				if(i==f) i=0;
			}
		}

	fclose(file);
	return 1;
}

float* mesh_get_vertices(Mesh* mesh) {
	int i,j,n=3*mesh->f;
	float *vertices = calloc(3*n, sizeof(float));

	for(i=0; i<n; i++) {
		for(j=0; j<3; j++) {
			vertices[i*3+j]=mesh->vertices[(mesh->triangles[i]-1)*3+j];
		}
	}

	return vertices;
}

float* mesh_get_normals(Mesh* mesh) {
	int i,j,n=3*mesh->f;
	float *normals = calloc(3*n, sizeof(float));

	for(i=0; i<n; i++) {
		for(j=0; j<3; j++) {
			normals[i*3+j]=mesh->normals[(mesh->normals_id[i]-1)*3+j];
		}
	}

	return normals;
}

void mesh_free(Mesh* mesh) {
	free(mesh->vertices);
	free(mesh->normals);
	free(mesh->triangles);
}
