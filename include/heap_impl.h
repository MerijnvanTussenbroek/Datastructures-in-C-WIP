#pragma once

#include <stdlib.h>
#include <stdio.h>
#include "binary_tree_impl.h"

/*This is a max-heap or min-heap depending on the comparison function you give*/

#define DEFINE_HEAP(name, type)     \
DEFINE_BINARY_TREE(name, type);     \