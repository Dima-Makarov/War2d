#pragma once

#include "GameObjects/vehicle.h"

class Player {
 private:
  static Player* instance;
  Player() = default;

 public:
  Player(const Player&) = delete;
  Player& operator=(Player&) = delete;

 public:
  static Player* Instance() {
    if (!instance)
      instance = new Player();
    return instance;
  }

  QString GetNickname() const;
  void SetNickname(const QString& nickname);
  QString GetCurrentVehicleId() const;
  QString GetCurrentVehicleId();
  void SetCurrentVehicleId(const QString& id);
  Vehicle* GetVehicle() const;
  void SetVehicle(Vehicle* vehicle);

 private:
  QString nickname_ = "not_set";
  QString vehicle_id_ = "tank";
  Vehicle* vehicle_ = nullptr;
};

