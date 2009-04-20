#ifndef TX_VMODEL_HPP
#define TX_VMODEL_HPP

#include "Visual.hpp"

/**
 * A class containing model information (but not the model itself).
 */
class VModel : public Visual {
	public:
		VModel();
		VModel(const string filename);
		virtual void draw(ResourceManager& rm);

	protected:
		string filename_;

	private:
		//Model* model_;
};

#endif
