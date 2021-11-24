#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <iostream>
#include <fstream>
#include <limits>
#include <cstddef>

unsigned long get_free_mem() {
    std::string token;
    std::ifstream file("/proc/meminfo");
    while(file >> token) {
        if(token == "MemFree:") {
            unsigned long mem;
            if(file >> mem) {
                return mem;
            } else {
                return 0;
            }
        }
        // Ignore the rest of the line
        file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return 0; // Nothing found
}

void getRAMInfo(){
	printf("Free RAM memory: %lu kB\n", get_free_mem());
}

int main (int argc, char *argv[]){

	const char* short_options = "V:L:hv:r";

	const struct option long_options[] = {
		{"help",	no_argument,		NULL,'h'},
		{"version",	no_argument,		NULL,'v'},
		{"ram",		no_argument,		NULL,'r'},
		{"Value",	required_argument,	NULL,'V'},
		{"List",	required_argument,	NULL,'L'},
		{NULL,		0,					NULL, 0},
	};

	int parse, option_index = -1;

	/* array for checking only unique items */
	bool counter[5] = {false, false, false, false, false};

	while ((parse=getopt_long(argc, argv, 
							short_options, 
							long_options, 
							&option_index))!=-1){
		switch(parse){
			/* -h or --help */
			case 'h': {
				if (!counter[0]){
					printf("Allowed commands:\n"
					       " -h, --help		get allowed options\n"
						   " -v, --version   	get current program version\n"
						   " -L, --List		set list\n"
						   " -V, --Value		set value\n"
						   " -r, --ram		get amount of RAM available\n");
					counter[0] = true;
				}
				break;
			}
			/* -v or --version */
			case 'v': {
				if (!counter[1]){
					printf("Program version is 1.0 .\n");
					counter[1] = true;
				}
				break;
			}

			/* -V or --Value with required argument */
			case 'V': {
				if (!counter[2]){
					printf("Value = %s\n",optarg);
					counter[2] = true;
				}
				break;
			}

			/* -L or --List with required list of arguments */
			case 'L': {
				if (!counter[3]){
					printf("List = %s\n",optarg);
					counter[3] = true;
				}
				break;
			}

			/* -r or --ram */
			case 'r': {
				if (!counter[4]){
					getRAMInfo();
					counter[4] = true;
				}
				break;
			}

			/* other unknown options */
			case '?': default: {
				printf("Bad option.\n");
				break;
			}
		}
		option_index = -1;
	}
	return 0;
}