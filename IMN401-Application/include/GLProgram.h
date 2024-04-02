/*
 *	(c) XLim, UMR-CNRS
 *	Authors: G.Gilet
 *  Documentation : J. Lemerle P. Le Gac
 */

#ifndef _GLPROGRAM_H
#define _GLPROGRAM_H

#include <glad/glad.h>
#include <string>
#include <stdexcept>

using namespace std;

class GLProgram
{
	public:

		//Attributs

		string info_text; //stocke les logs retournés par opengl

		//Constructeur-Destructeur

		/**
			Constructeur de la classe GLProgram prenant en paramètre son nom et son type
			Permet de récupérer le GLProgramSource correspondant au nom grâce à GLProgramSourceManager, crée un nouveau GLUniformManager et détermine le type du programme
			@param name : nom du programme
			@param type : type du programme
		*/
		GLProgram(std::string name,GLenum type);

		/**
			Destructeur de la classe qui appelle la fonction release du GLProgramSourceManager
		*/
		~GLProgram();

		//Méthodes


		/**
			Méthode retournant l'adresse mémoire alloué à l'instance du programme opengl
			@return : adresse mémoire du programme
		*/
		GLuint getId();

	
		/**
			Méthode affichant les erreurs du programme
			@return : compilation réussie du programme
		*/
		bool printInfoLog();

	private:

		//Attributs
		string m_filename;
		GLuint m_Id; // nom associé à l'instance de GLProgram
		GLenum m_Type; //type du programme (vf, fs, gs, etc ...)
		
};





#endif
