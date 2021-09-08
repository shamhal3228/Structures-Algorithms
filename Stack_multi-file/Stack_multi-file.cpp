#include <iostream>
#include <string>
#include "stack.h"

using namespace std;

int main()
{
	s_stack sa, sb;
	string a, b;
	cin >> a >> b;

	for (int i = 0; i < a.size(); i++)
		sa.s_push(a[i] - '0');

	for (int i = 0; i < b.size(); i++)
		sb.s_push(b[i] - '0');

	s_stack res;
	int d = 0;
	while (!(sa.s_empty() && sb.s_empty()))
	{
		int f = 0, s = 0;
		if (!sa.s_empty())
			f = sa.s_pop();

		if (!sb.s_empty())
			s = sb.s_pop();

		int t = f + s + d;
		d = t / 10;
		res.s_push(t % 10);
	}

	if (d != 0)
		res.s_push(d);

	while (!res.s_empty())
		cout << res.s_pop();
}