// Copyright 2012 Kevin Darlington

#ifndef OFFSETS_0_1_0_495_H_
#define OFFSETS_0_1_0_495_H_

#define QUAKELIVE_Cmd_ExecuteStringType 0x9C6F0
// Found by searching for "cl_timeout" parameter and seeing what function it was being called with.
#define QUAKELIVE_Cvar_Get 0xA1870

// Found address by searching disassembly for "ent:%3i"
#define CGAME_CG_EntityEvent 0x14E30
#define CGAME_CG_DrawActiveFrame 0x41770
// Index of item_armor_shard.
// Found by disassembling CG_EntityEvent and looking how it used bg_itemlist inside
// of the EV_ITEM_PICKUP case.  
#define CGAME_bg_itemlist_item_armor_shard 0x57174
// Found by searching for "CG_MapRestart"
#define CGAME_CG_MapRestart 0x3E060

#endif
