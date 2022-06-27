#pragma once

#include <QObject>
#include "Model/vec2f.h"

class GameObject : public QObject {
 Q_OBJECT
 public:
  GameObject(const Vec2f& position, const Vec2f& orientation);
  virtual void Update(int millis) = 0;
  virtual Vec2f GetPosition() const;
  virtual Vec2f GetOrientation() const;
  virtual QPixmap GetPixmap() const = 0;

 protected:
  Vec2f position_;
  Vec2f orientation_;
};




