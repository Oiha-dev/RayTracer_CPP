#pragma once

#include <memory>
#include "object.h"

class world {
public:
    std::vector<std::shared_ptr<object>> objects;

    explicit world(std::vector<std::shared_ptr<object>> objs);
};