//
// Created by smarty on 22.10.2020.
//

#ifndef ZOO_ANIMALS_H
#define ZOO_ANIMALS_H
#include <string>

class Animal {
public:
    virtual std::string Voice() const {
        return "Not implemented yet";
    }
    virtual ~Animal() {
    }
};


class Tiger: public Animal {
    std::string Voice() const override {
        return "Rrrr";
    }
};


class Wolf: public Animal {
    std::string Voice() const override {
        return "Wooo";
    }
};


class Fox: public Animal {
    std::string Voice() const override {
        return "Tyaf";
    }
};


#endif //ZOO_ANIMALS_H
