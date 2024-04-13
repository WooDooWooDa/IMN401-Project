#pragma once

#include "EffectGL.h"

#include "Texture2D.h"

class EffectBlur : public EffectGL
{
public:


	//Constructeur-Destructeur
	EffectBlur(string name);

	/**
		Destructeur de la classe
	*/
	~EffectBlur();

	//Méthodes

	/**
		Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
		@param o : Node/Objet pour lequel on veut effectuer le rendu
	*/
	virtual void apply(FrameBufferObject* src, FrameBufferObject* target);

	/**
		Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
		@param o : Node/Objet concerné par le rendu
		@param elapsedTime : temps
	*/
	virtual void animate(const float elapsedTime);


	virtual void displayInterface() {};
	void setDepth(FrameBufferObject* depthFBO) { depth = depthFBO; }


protected:
	GLProgram* vp;
	GLProgram* fp;

	GLint l_Direction;
	FrameBufferObject *tmp;
	FrameBufferObject* depth;


};