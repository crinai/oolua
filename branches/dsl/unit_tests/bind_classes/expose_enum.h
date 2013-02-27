#ifndef EXPOSE_ENUM_PARAM_H_
#	define EXPOSE_ENUM_PARAM_H_

#include "oolua.h"
#include "cpp_enum.h"

OOLUA_PROXY_CLASS(Enums)
	OOLUA_TYPEDEFS Register_class_enums OOLUA_END_TYPES
	OOLUA_CONSTRUCTORS_BEGIN
		OOLUA_CONSTRUCTOR(Enums::COLOUR)
	OOLUA_CONSTRUCTORS_END
	OOLUA_ENUMS_START
		OOLUA_ENUM_ENTRY(GREEN)
		OOLUA_ENUM_ENTRY(INVALID)
	OOLUA_ENUMS_END
	OOLUA_MEM_FUNC(void,set_enum,Enums::COLOUR)
	OOLUA_MEM_FUNC(Enums::COLOUR,get_enum)
OOLUA_CLASS_END

#endif
