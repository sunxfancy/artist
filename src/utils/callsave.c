/* 
* @Author: sxf
* @Date:   2015-06-03 15:27:37
* @Last Modified by:   sxf
* @Last Modified time: 2015-06-03 16:16:53
*/

#include "callsave.h"
#include <stdio.h>

int callsave_getsize(const char* type) {
	int size = 0;
	for (const char* p = type; p != 0; ++p) {
		switch(*p) {
			case 'i' : size += sizeof(int); break;
			case 'd' : size += sizeof(double); break;
			case 's' : size += sizeof(const char*); break;
			case 'f' : size += sizeof(void*); break;
			case 'b' : size += sizeof(bool); break;
			default:
				printf("Callsave type erro.\n"); return -1;
		}
	}
	return size;
}