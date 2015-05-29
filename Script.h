/*
 * Script.h
 *
 *  Created on: 1 mars 2015
 *      Author: Gabriel
 */

#ifndef SCRIPT_H_
#define SCRIPT_H_

/* A script is a gameplay code assigned to a scene object or a scene.
 * To use of script, you need to assigned two functions :
 * - setup : This function is executed when initializing a scene or a scene object.
 * - run : This function is executed each frame.
 */

#define define_script(type)\
	char* name;\
	void (*setup) (struct type*, SceneObject*);\
	void (*run) (struct type*, SceneObject*);
#define setup_script(type) void (*setup) (struct type*, SceneObject*)
#define run_script(type) void (*run) (struct type*, SceneObject*)

typedef struct Script Script;
typedef struct SceneObject SceneObject;
typedef void (*fct_script) (Script*, SceneObject*);

struct Script {
	define_script(Script);
};

#endif /* SCRIPT_H_ */
