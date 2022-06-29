#include <QLabel>
#include "hangar.h"
#include "Model/player.h"

Hangar::Hangar(QWidget*)
    : to_battle_(new QPushButton("To battle!")),
      v_layout_(new QVBoxLayout(this)),
      vehicle_combo_box_(new QComboBox()) {
  v_layout_->addWidget(to_battle_,3,Qt::AlignCenter);
  v_layout_->addWidget(new QLabel("money: UNIMPLEMENTED$"), 1, Qt::AlignCenter);
  v_layout_->addStretch(10);
  v_layout_->addWidget(vehicle_combo_box_, 3, Qt::AlignCenter);
  vehicle_combo_box_->addItem(QIcon(PixmapLoader::Instance()->tank),"tank");
  vehicle_combo_box_->addItem(QIcon(PixmapLoader::Instance()->ship),"ship");
  vehicle_combo_box_->addItem(QIcon(PixmapLoader::Instance()->plane),"plane");

  connect(to_battle_, &QPushButton::clicked, this, &Hangar::StartBattle);
  connect(vehicle_combo_box_, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &Hangar::SelectVehicle);
}

void Hangar::StartBattle() {
  emit ToBattle();
}

void Hangar::SelectVehicle(int) {
  Player::Instance()->SetCurrentVehicleId(vehicle_combo_box_->currentText());
}
