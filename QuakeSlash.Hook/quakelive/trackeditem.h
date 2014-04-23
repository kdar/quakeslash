// Copyright 2012 Kevin Darlington

#ifndef TRACKEDITEM_H_
#define TRACKEDITEM_H_

#include <vector>

#include "datastructures.h"

//enum TrackedItemType
//{
//  TRACKEDITEM_UNKNOWN,
//  TRACKEDITEM_ARMOR,
//  TRACKEDITEM_HEALTH,
//  TRACKEDITEM_WEAPON
//};
//
//enum TrackedItemArmorType
//{
//  TRACKEDITEM_ARMOR_RED,
//  TRACKEDITEM_ARMOR_YELLOW
//};
//
//enum TrackedItemHealthType
//{
//  TRACKEDITEM_HEALTH_MEGA
//};
//

// Maximum distance two entity's coordinates can be while still
// being considered the same entity.
#define MAX_MODEL_DISTANCE 150.0

//---------------------------------------
class TrackedItem
{
public:
  TrackedItem(itemType_t item, int quantity, vec3_t lerpOrigin, int servertime, entity_event_t event);

public:
  itemType_t item_;
  int quantity_;
  vec3_t lerpOrigin_;
  int servertime_;
  entity_event_t event_;
};

//---------------------------------------
class TrackedItemManager {
public:
  TrackedItemManager();
  ~TrackedItemManager();

  void Action(TrackedItem* item);
  bool Changed();
  void Clear()
  { items_.clear(); }

public:
  bool changed_;
  std::vector<TrackedItem*> items_;
};

#endif
