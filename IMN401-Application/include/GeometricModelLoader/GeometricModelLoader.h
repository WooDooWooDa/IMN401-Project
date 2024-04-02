#ifndef _GEOEMTRICAL_Node_LOADER_
#define _GEOEMTRICAL_Node_LOADER_


#include <string>
using namespace std;
class GeometricModel;

class GeometricModelLoader
{
	public:
		GeometricModelLoader(){};
		~GeometricModelLoader(){};
		virtual bool loadModel(string name,GeometricModel *model) = 0;

};
#endif
