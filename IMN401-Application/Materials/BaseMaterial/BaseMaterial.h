

#ifndef _BaseMaterial_
#define _BaseMaterial_


#include "MaterialGL.h"

class BaseMaterial : public MaterialGL
{
	public :

		//Attributs
		
		//Constructeur-Destructeur

		/**
			Constructeur de la classe à partir du nom du matériau 
			@param name : nom du matériau
		*/
		BaseMaterial(string name="");

		/**
			Destructeur de la classe
		*/
		~BaseMaterial();

		//Méthodes

		/**
			Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
			@param o : Node/Objet pour lequel on veut effectuer le rendu
		*/
		virtual void render(Node *o);

		/**
			Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
			@param o : Node/Objet concerné par le rendu
			@param elapsedTime : temps écoulé depuis la dernière frame
		*/
		virtual void animate(Node* o, const float elapsedTime);


		virtual void displayInterface() {};

		
	protected :
		GLProgram* vp;
		GLProgram* fp;

		GLuint l_View,l_Proj, l_Model;

		std::chrono::steady_clock::time_point timeStart;

};

#endif