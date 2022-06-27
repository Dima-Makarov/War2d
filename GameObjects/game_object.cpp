
#include "game_object.h"

Vec2f GameObject::GetPosition() const {
  return position_;
}

Vec2f GameObject::GetOrientation() const {
  return orientation_;
}

GameObject::GameObject(const Vec2f& position, const Vec2f& orientation) : QObject(
    nullptr), position_(position), orientation_(orientation) {}
