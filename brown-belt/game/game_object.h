//
// Created by smarty on 15.10.2020.
//

#ifndef GAME_GAME_OBJECT_H
#define GAME_GAME_OBJECT_H

class Unit;
class Building;
class Tower;
class Fence;

struct GameObject {
    virtual ~GameObject() = default;

    virtual bool Collide(const GameObject& that) const = 0;
    virtual bool CollideWith(const Unit& that) const = 0;
    virtual bool CollideWith(const Building& that) const = 0;
    virtual bool CollideWith(const Tower& that) const = 0;
    virtual bool CollideWith(const Fence& that) const = 0;
};

bool Collide(const GameObject& first, const GameObject& second);

#endif //GAME_GAME_OBJECT_H
