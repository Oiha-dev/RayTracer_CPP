#include "header/world.h"

world::world(std::vector<std::shared_ptr<object>> objs) {
    objects = std::move(objs);
}
