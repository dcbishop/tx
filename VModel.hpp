#ifndef TX_VMODEL_HPP
#define TX_VMODEL_HPP

#include "Visual.hpp"

/**
 * A class containing model information (but not the model itself).
 */
class VModel : public Visual {
	public:
		//VModel();
		VModel(const string filename="");
		virtual void draw(ResourceManager& rm);
		virtual string getFilename();
		virtual void setFilename(string filename);

	private:
		string filename_;
};

#endif /* TX_VMODEL_HPP */
