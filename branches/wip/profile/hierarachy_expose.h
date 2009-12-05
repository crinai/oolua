#ifndef HIERARACHY_OOLUA_H_
#	define HIERARACHY_OOLUA_H_

#include "hierarchy.h"
#include "oolua.h"

OOLUA_CLASS_NO_BASES(ProfileBase)
	OOLUA_NO_TYPEDEFS
	OOLUA_MEM_FUNC_1(void,increment_a_base,ProfileBase*)
OOLUA_CLASS_END

OOLUA_CLASS_NO_BASES(ProfileAnotherBase)
	OOLUA_NO_TYPEDEFS
OOLUA_CLASS_END


OOLUA_CLASS(ProfileDerived) : public Proxy_class<ProfileBase>
	OOLUA_BASIC
	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START ProfileBase OOLUA_BASES_END
OOLUA_CLASS_END

OOLUA_CLASS(ProfileMultiBases) :public Proxy_class<ProfileAnotherBase>, public Proxy_class<ProfileBase>
	OOLUA_BASIC
	OOLUA_NO_TYPEDEFS
	OOLUA_BASES_START ProfileAnotherBase,ProfileBase OOLUA_BASES_END
OOLUA_CLASS_END

void open_Luabind_hierarchy(lua_State* l);


#endif