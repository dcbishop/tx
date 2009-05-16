#ifndef TX_VMODEL_HPP
#define TX_VMODEL_HPP
#include <string>
using namespace std;

#include "Visual.hpp"

class Interface;

const string MODEL_DEFAULT = "pointer.dae";
const string MODEL_CUBE = "cube.dae";
const string MODEL_ROBOT = "monkey-robot.dae";

/**
 * A class containing model information (but not the model itself).
 */
class VModel : public Visual {
	public:
		//VModel();
		VModel(const string filename="");
		virtual void draw(Interface* rm);
		virtual string getFilename();
		virtual void setFilename(string filename);

	private:
		string filename_;
};

#endif /* TX_VMODEL_HPP */
