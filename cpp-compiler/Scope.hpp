#pragma once

#include "HashTable.hpp"
#include "NamedValue.hpp"

class Scope {
public:
    HashTable<NamedValue> local;
    Scope *parent = nullptr;
};
