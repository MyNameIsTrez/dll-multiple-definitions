#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

typedef int (*foo)(void);

int main() {
	foo f1;
	foo f2;

	void *handle1 = dlopen("./dll1.dll", RTLD_NOW);
	if (!handle1) { fprintf(stderr, "%s\n", dlerror()); exit(EXIT_FAILURE); }
	void *handle2 = dlopen("./dll2.dll", RTLD_NOW);
	if (!handle2) { fprintf(stderr, "%s\n", dlerror()); exit(EXIT_FAILURE); }

	/*
	The reason we call dlerror() is explained in `man 3 dlsym`:
	In unusual cases (see NOTES) the value of the symbol could actually be NULL.
	Therefore, a NULL return from dlsym() need not indicate an error.
	The correct way to distinguish an error from a symbol whose value is NULL
	is to call dlerror(3) to clear any old error conditions, then call dlsym(),
	and then call dlerror(3) again, saving its return value into a variable,
	and check whether this saved value is not NULL.
	*/
	dlerror();
	f1 = (foo)dlsym(handle1, "foo");
	char *err1 = dlerror();
	if (err1) { fprintf(stderr, "%s\n", err1); exit(EXIT_FAILURE); }
	dlerror();
	f2 = (foo)dlsym(handle2, "foo");
	char *err2 = dlerror();
	if (err2) { fprintf(stderr, "%s\n", err2); exit(EXIT_FAILURE); }

	printf("%d\n", f1());
	printf("%d\n", f2());

	if (dlclose(handle1)) { fprintf(stderr, "%s\n", dlerror()); exit(EXIT_FAILURE); }
	if (dlclose(handle2)) { fprintf(stderr, "%s\n", dlerror()); exit(EXIT_FAILURE); }
}
