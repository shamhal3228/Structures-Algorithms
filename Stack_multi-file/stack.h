#pragma once

#include "node.h"

struct s_stack
{
public:
	node* last = 0;
	bool s_empty();
	void s_push(int v);
	int s_pop();
};