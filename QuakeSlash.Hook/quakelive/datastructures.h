// Copyright 2012 Kevin Darlington

#ifndef QUAKELIVE_DATASTRUCTURES_H_
#define QUAKELIVE_DATASTRUCTURES_H_

typedef float vec_t;
typedef vec_t vec2_t[2];
typedef vec_t vec3_t[3];
typedef enum {qfalse, qtrue} qboolean;
#define	EV_EVENT_BIT1		0x00000100
#define	EV_EVENT_BIT2		0x00000200
#define	EV_EVENT_BITS		(EV_EVENT_BIT1|EV_EVENT_BIT2)

typedef enum {
  EV_ITEM_PICKUP = 15,
  EV_ITEM_RESPAWN = 37
} entity_event_t;

// Reverse engineered from various functions
// inside cg_event.c.
typedef struct 
{
  char unknown[168];
  int	modelindex;
  int	modelindex2;
  int clientNum;
  int	frame;
  int	solid;			// for client side prediction, trap_linkentity sets this properly
  int event;
  int eventParam;
  char unknown2[20];
} entityState_t; //size dec: 216

// Reverse engineered from various functions
// inside cg_event.c.
typedef struct
{
  entityState_t currentState;
  entityState_t nextState;
  int        interpolate;
  int        currentValid;                  
  char       unknown2[32];
  int        centFrame;
  char       unknown3[172]; 
  vec3_t     lerpOrigin;//dec: 648
  vec3_t     lerpAngles;
}centity_t;//size hex: 2A0 dec: 672

// Exact same as Quake3
typedef enum {
  IT_BAD,
  IT_WEAPON,				// EFX: rotate + upscale + minlight
  IT_AMMO,				// EFX: rotate
  IT_ARMOR,				// EFX: rotate + minlight
  IT_HEALTH,				// EFX: static external sphere + rotating internal
  IT_POWERUP,				// instant on, timer based
  // EFX: rotate + external ring that rotates
  IT_HOLDABLE,			// single use, holdable item
  // EFX: rotate + bob
  IT_PERSISTANT_POWERUP,
  IT_TEAM
} itemType_t;

#define MAX_ITEM_MODELS 4

// Exact same as Quake3
typedef struct gitem_s {
  char		*classname;	// spawning name
  char		*pickup_sound;
  char		*world_model[MAX_ITEM_MODELS];

  char		*icon;
  char		*pickup_name;	// for printing on pickup

  int			quantity;		// for ammo how much, or duration of powerup
  itemType_t  giType;			// IT_* flags

  int			giTag;

  char		*precaches;		// string of all models and images this item will use
  char		*sounds;		// string of all sounds this item will use
} gitem_t;

// This was taken from Quake3 source. Not sure if this is entirely accurate
// but at least name and string work, which is all we need.
typedef struct cvar_s {
  char		*name;
  char		*string;
  char		*resetString;		// cvar_restart will reset to this value
  char		*latchedString;		// for CVAR_LATCH vars
  int			flags;
  qboolean	modified;			// set each time the cvar is changed
  int			modificationCount;	// incremented each time the cvar is changed
  float		value;				// atof( string )
  int			integer;			// atoi( string )
  struct cvar_s *next;
  struct cvar_s *hashNext;
} cvar_t;

#endif
