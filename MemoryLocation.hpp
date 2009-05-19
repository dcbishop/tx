#ifndef TX_MEMORYLOCATION_HPP
#define TX_MEMORYLOCATION_HPP

/**
 * A class for passing the memory location to Lua
 */
class MemoryLocation {
	public:
		virtual long getMemoryAddress();
};

#endif // TX_MEMORYLOCATION_HPP
