#pragma once

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QComboBox>

class Hangar : public QWidget {
  Q_OBJECT
 public:
  Hangar(QWidget* parent = nullptr);

 signals:
  void ToBattle();

 private:
  void SelectVehicle(int index);
  void StartBattle();
  QPushButton* to_battle_;
  QVBoxLayout* v_layout_;
  QComboBox* vehicle_combo_box_;
};



