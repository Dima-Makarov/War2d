
#pragma once

#include "GameObjects/vehicle.h"

class Player {
 public:
  Player() = default;

  size_t GetId() const;
  void SetId(size_t id);

  Vehicle* GetCurrentVehicle() const;
  Vehicle* GetCurrentVehicle();
  void SetCurrentVehicle(Vehicle* vehicle);

 private:
  size_t id_ = 0;
  Vehicle* current_vehicle_ = nullptr;
};

