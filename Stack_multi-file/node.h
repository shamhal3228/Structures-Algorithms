#pragma once

struct node
{
	node* next = nullptr;
	int value;
	node(int v);
};