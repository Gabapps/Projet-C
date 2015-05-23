/*
 * Audio.c
 *
 *  Created on: 1 mai 2015
 *      Author: max
 */

#include "Audio.h"


int initOpenAL()
{
    // Ouverture du device
    ALCdevice* Device = alcOpenDevice(NULL);
    if (!Device)
        return 0;

    // Cr�ation du contexte
    ALCcontext* Context = alcCreateContext(Device, NULL);
    if (!Context)
        return 0;

    // Activation du contexte
    if (!alcMakeContextCurrent(Context))
        return 0;

    return 1;
}


void shutdownOpenAL()
{
    // R�cup�ration du contexte et du device
    ALCcontext* Context = alcGetCurrentContext();
    ALCdevice*  Device  = alcGetContextsDevice(Context);

    // D�sactivation du contexte
    alcMakeContextCurrent(NULL);

    // Destruction du contexte
    alcDestroyContext(Context);

    // Fermeture du device
    alcCloseDevice(Device);
}

ALuint loadSound(char* filename)
{
    // Ouverture du fichier audio avec libsndfile
    SF_INFO FileInfos;
    SNDFILE* File = sf_open(filename, SFM_READ, &FileInfos);
    if (!File)
        return 0;

    // Lecture du nombre d'�chantillons et du taux d'�chantillonnage (nombre d'�chantillons � lire par seconde)
    ALsizei NbSamples  = (ALsizei)(FileInfos.channels * FileInfos.frames);
    ALsizei SampleRate = (ALsizei)(FileInfos.samplerate);

    // Lecture des �chantillons audio au format entier 16 bits sign� (le plus commun)
//    std::vector<ALshort> Samples(NbSamples);
    ALshort* Samples = (ALshort*) malloc(NbSamples * sizeof(ALshort));
    if (sf_read_short(File, &Samples[0], NbSamples) < NbSamples)
         return 0;

    sf_close(File);

    ALenum Format;
    switch (FileInfos.channels)
    {
        case 1 :
        	Format = AL_FORMAT_MONO16;
        	break;
        case 2 :
        	Format = AL_FORMAT_STEREO16;
        	break;
        default :
        	return 0;
    }

    ALuint Buffer;
    alGenBuffers(1, &Buffer);

    alBufferData(Buffer, Format, &Samples[0], NbSamples * sizeof(ALushort), SampleRate);

    // V�rification des erreurs
    if (alGetError() != AL_NO_ERROR)
        return 0;

    return Buffer;
}

void setupListener(float x, float y, float z, float u, float v, float w)
{
	// D�finition de la position de l'�couteur (ici l'origine)
	alListener3f(AL_POSITION, x, y, z);

	// D�finition de la vitesse de l'�couteur (ici nulle)
	alListener3f(AL_VELOCITY, 0.f, 0.f, 0.f);

	// D�finition de l'orientation de l'�couteur (ici il regarde vers l'axe des Z)
	ALfloat Orientation[] = {u, v, w, 0.f, 1.f, 0.f};
	alListenerfv(AL_ORIENTATION, Orientation);
}

Sound* addSound(char* filename, list_sound* sounds, float pitch)
{
	Sound* sound = malloc(sizeof(Sound));
	sound->buffer = loadSound(filename);

	sound->status = AL_PLAYING;

	alGenSources(1, &(sound->source));

	alSourcef(sound->source, AL_PITCH, pitch);



	alSourcei(sound->source, AL_BUFFER, sound->buffer);
//	alSource3f(source, AL_POSITION, 5.f, 0.f, 0.f);

	alSourcePlay(sound->source);
	alGetSourcei(sound->source, AL_SOURCE_STATE, &(sound->status));



	list_sound_put(sounds, sound);

	return sound;
}

Sound* createSound(char* filename, float pitch)
{
	Sound* sound = malloc(sizeof(Sound));
	sound->buffer = loadSound(filename);

	sound->status = AL_PLAYING;

	alGenSources(1, &(sound->source));

	alSourcef(sound->source, AL_PITCH, pitch);



	alSourcei(sound->source, AL_BUFFER, sound->buffer);
//	alSource3f(source, AL_POSITION, 5.f, 0.f, 0.f);

	alSourcePlay(sound->source);
	alGetSourcei(sound->source, AL_SOURCE_STATE, &(sound->status));

	return sound;
}

list_sound* initSoundList()
{
	return list_sound_create();
}

void removeSound(Sound* sound, list_sound* sounds)
{
	list_sound_delete(sounds, sound, 1);
}

void playSounds(list_sound* sounds)
{
	node_sound *iterator = sounds->root;

	while(iterator != NULL)
	{
		//*(iterator->value->status) == AL_PLAYING
		if(iterator->value->status == AL_PLAYING)
		{
			alGetSourcei(iterator->value->source, AL_SOURCE_STATE, &(iterator->value->status));
		}
		else
		{
			// Destruction du tampon
			alDeleteBuffers(1, &(iterator->value->buffer));

			// Destruction de la source
			alSourcei(iterator->value->source, AL_BUFFER, 0);
			alDeleteSources(1, &(iterator->value->source));

			// On enleve de la liste des sons
			removeSound(iterator->value, sounds);
		}
		iterator = iterator->next;
	}
}
