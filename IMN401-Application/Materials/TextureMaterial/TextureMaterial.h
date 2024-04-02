

#ifndef _TextureMaterial_
#define _TextureMaterial_


#include "MaterialGL.h"
#include "Texture2D.h"




struct Texture {
	glm::vec4 coeff;// les parametres de Texture : coeff.x : ka, coeff.y = kd, coeff.z : ks, coeff.w : s
	glm::vec3 albedo; // La couleur diffuse
};




class TextureMaterial : public MaterialGL
{
public:

	//Attributs

	//Constructeur-Destructeur

	/**
		Constructeur de la classe � partir du nom du mat�riau
		@param name : nom du mat�riau
	*/
	TextureMaterial(string name = "");

	/**
		Destructeur de la classe
	*/
	~TextureMaterial();

	//M�thodes
	void addAlbedoMap(Texture2D * texture, Texture2D * texture2 = NULL);
	void addNormalMap(Texture2D* normal);
	void addAOMap(Texture2D* ao);
	void addDispMap(Texture2D* disp, float factor = 1.0);
	/**
		M�thode virtuelle qui est appel�e pour faire le rendu d'un objet en utilisant ce mat�riau
		@param o : Node/Objet pour lequel on veut effectuer le rendu
	*/
	virtual void render(Node* o);

	/**
		M�thode virtuelle qui est appel�e pour modifier une valeur d'un param�tre n�cessaire pour le rendu
		@param o : Node/Objet concern� par le rendu
		@param elapsedTime : temps
	*/
	virtual void animate(Node* o, const float elapsedTime);



	 void updatePhong();

	virtual void displayInterface() ;


protected:
	GLProgram* vp;
	GLProgram* fp;

	float hasAOMap = false;
	GLuint l_View, l_Proj, l_Model, l_PosLum, l_PosCam, l_Phong, l_Albedo, l_Time, l_hasAOMap;
	GLuint l_Texture, l_Texture2, l_normalMap, l_aoMap, l_disp;
	Texture param;

};

#endif