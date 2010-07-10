#if 0 // Not used...
#ifndef TX_SCALE_HPP
#define TX_SCALE_HPP

/**
 * A class for rotation information.
 */
class Scale {
	public:
		virtual void setScale(const float sx, const float sy, const float sz);
		virtual void setScaleX(const float sx);
		virtual void setScaleY(const float sy);
		virtual void setScaleZ(const float sz);
		virtual const float getScaleX();
		virtual const float getScaleY();
		virtual const float getScaleZ();

		protected:
			virtual void setScale_();

	private:
		float sx_;
		float sy_;
		float sz_;
};

#endif /* TX_SCALE_HPP */
#endif /* 0 */
