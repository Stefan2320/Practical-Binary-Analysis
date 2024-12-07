#include <dlfcn.h> // to get pointers to the shared library functions
#include <string.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <unistd.h>


DIR* (*original_opendir)(const char* name);

DIR* opendir(const char* name){
	// If the name is not in the home path, exit
	char name_path[1024] ;
	const char *home_path = getenv("HOME");
        
	getcwd(name_path,sizeof(name_path));
	if(strcmp(name_path, home_path)){
		fprintf(stderr,"You're not allowed to use ls outside of the home path...\n");
		exit(1);
	}
	printf("%s\n",name_path);

	// Get a pointer to the original opendir function (NEXT flag is used to get the NEXT version of opendir from the chain)
	if(!original_opendir) original_opendir = dlsym(RTLD_NEXT, "opendir");


	DIR *original = original_opendir(home_path);
	return original;
}


