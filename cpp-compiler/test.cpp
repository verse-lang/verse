#include <cstdio>

int main() {
	char c = 0;
	do {
		if (c == '!' || c >= '#' && c <= '&' || c >= '*' && c <= '/' ||
			c >= ':' && c <= '@' || c == '^' || c == '_' || c == '|' ||
			c == '~') {
			printf("%c", c);
		}
	} while (++c != 0);
	getchar();
	return 0;
}
