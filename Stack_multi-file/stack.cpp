#include "stack.h"

void s_stack::s_push(int v)
{
	node* n = new node(v);
	n->next = last;
	last = n;
}

int s_stack::s_pop()
{
	node* temp = last;
	if (last->next != nullptr)
		last = last->next;
	else
		last = nullptr;
	int resp = temp->value;
	delete temp;
	return resp;
}

bool s_stack::s_empty()
{
	return last == nullptr;
}