#ifndef WORLD_H
#define WORLD_H
#include <memory>
#include <utility>

#include "object.h"


class world {
public:
    std::vector<std::shared_ptr<object>> objects;

    explicit world(std::vector<std::shared_ptr<object>> objs) {
        objects = std::move(objs);
    }
};

#endif //WORLD_H
