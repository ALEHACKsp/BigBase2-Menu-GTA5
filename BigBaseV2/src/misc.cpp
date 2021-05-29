#include "pointers.hpp"

namespace big::misc
{
	void set_global(uint32_t address, int64_t value)
	{
		g_pointers->m_script_globals[(address >> 0x12) & 0x3F][address & 0x3FFFF] = value;
	}
};