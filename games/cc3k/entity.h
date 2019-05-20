#ifndef __ENTITY_H__
#define __ENTITY_H__

class Entity {
  char rep;
 public:
  explicit Entity (char rep): rep(rep) {}
  const char repn() const { return rep; }
  virtual ~Entity() = 0;
};

#endif
