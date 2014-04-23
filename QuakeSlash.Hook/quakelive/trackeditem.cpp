#include "trackeditem.h"

//=======================================
TrackedItem::TrackedItem(itemType_t item, int quantity, vec3_t lerpOrigin, int servertime, entity_event_t event)
  : item_(item), 
  quantity_(quantity),
  servertime_(servertime),
  event_(event)
{
  lerpOrigin_[0] = lerpOrigin[0];
  lerpOrigin_[1] = lerpOrigin[1];
  lerpOrigin_[2] = lerpOrigin[2];
}

//=======================================
TrackedItemManager::TrackedItemManager() 
  : changed_(false)
{
}

//=======================================
TrackedItemManager::~TrackedItemManager()
{
  for(std::vector<TrackedItem*>::iterator it = items_.begin(); it != items_.end(); ++it) {
    delete (*it);
  }
}

//=======================================
void TrackedItemManager::Action(TrackedItem* item)
{
  bool found = false;
  for(std::vector<TrackedItem*>::iterator it = items_.begin(); it != items_.end(); ++it) {
    double distance = pow((*it)->lerpOrigin_[0] - item->lerpOrigin_[0], 2) + 
      pow((*it)->lerpOrigin_[1] - item->lerpOrigin_[1], 2) + 
      pow((*it)->lerpOrigin_[2] - item->lerpOrigin_[2], 2);
    distance = sqrt(distance);

    // assume because the two models are less than the MAX_MODEL_DISTANCE that
    // they are the same item.
    if (distance <= MAX_MODEL_DISTANCE && item->item_ == (*it)->item_ && item->quantity_ == (*it)->quantity_) {
      if (item->event_ == EV_ITEM_PICKUP) {
        (*it)->servertime_ = item->servertime_;          
      }
      (*it)->event_ = item->event_;
      found = true;
      break;
    }
  }   

  // We didn't find a match. Add it to our vector.
  if (!found) {
    items_.push_back(item);
  }

  changed_ = true;
}

//=======================================
bool TrackedItemManager::Changed()
{
  bool ret = changed_;
  changed_ = false;
  return ret;
}
