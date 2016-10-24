#include "Script.h"

namespace sp { namespace spjs {

	Script::Script() { }
	
	Script::~Script()
	{
		spdel m_MHS;
		spdel m_RS;
	}

} }