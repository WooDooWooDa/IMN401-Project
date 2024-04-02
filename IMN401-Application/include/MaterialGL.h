

#ifndef _MATERIALGL_
#define _MATERIALGL_


#include "GLProgramPipeline.h"
#include "Scene.h"
class Node;

class MaterialGL
{
	public :

		//Attributs

		GLProgramPipeline* m_ProgramPipeline;
		
		//Constructeur-Destructeur

		/**
			Constructeur de la classe à partir du nom du matériau 
			@param name : nom du matériau
		*/
		MaterialGL(string name="");

		/**
			Destructeur de la classe
		*/
		~MaterialGL();

		//Méthodes

		/**
			Méthode virtuelle qui est appelée pour faire le rendu d'un objet en utilisant ce matériau
			@param o : Node/Objet pour lequel on veut effectuer le rendu
		*/
		virtual void render(Node *o);

		/**
			Méthode virtuelle qui est appelée pour modifier une valeur d'un paramètre nécessaire pour le rendu
			@param o : Node/Objet concerné par le rendu
			@param elapsedTime : temps
		*/
		virtual void animate(Node* o, const float elapsedTime);


		string getName() { return m_Name; };

		virtual void displayInterface() {};

		
	protected :
		std::string m_Name;

		Scene* scene;
};

#endif