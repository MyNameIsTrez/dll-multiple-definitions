#include <windows.h>
#include <stdio.h>

typedef int (*foo)(void);

int main() {
	foo f1;
	foo f2;

	HMODULE dll1 = LoadLibraryA("dll1.dll");
	if (!dll1) { fprintf(stderr, "LoadLibraryA() error\n"); exit(EXIT_FAILURE); }
	HMODULE dll2 = LoadLibraryA("dll2.dll");
	if (!dll2) { fprintf(stderr, "LoadLibraryA() error\n"); exit(EXIT_FAILURE); }

	f1 = (foo)GetProcAddress((HMODULE)dll1, "foo");
	if (!f1) { fprintf(stderr, "GetProcAddress() error\n"); exit(EXIT_FAILURE); }
	f2 = (foo)GetProcAddress((HMODULE)dll2, "foo");
	if (!f2) { fprintf(stderr, "GetProcAddress() error\n"); exit(EXIT_FAILURE); }

	printf("%d\n", f1());
	printf("%d\n", f2());
	
	if (!FreeLibrary((HMODULE)dll1)) { fprintf(stderr, "FreeLibrary() error\n"); exit(EXIT_FAILURE); }
	if (!FreeLibrary((HMODULE)dll2)) { fprintf(stderr, "FreeLibrary() error\n"); exit(EXIT_FAILURE); }
}
