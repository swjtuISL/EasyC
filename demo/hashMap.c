#include <stdio.h>
#include "HashMap.h"

void testHashMap1(){
	HashMap *map = newHashMap(NULL);
	map->putChars(map, "name", "lsj");
	map->putInt(map, "age", 24);
	map->putFloat(map, "weight", 60.6);


	printf("%s", toChars(map->toString(map)));

	freeHashMap(map);
}

void testHashMap2(){
	char *strs[] = { "happy", "no", "hello", "ko", "happy", "ko", "ko" };
	HashMap *map = newHashMap(NULL);

	for (int i = 0; i < sizeof(strs) / sizeof(char*); i++){
		char *s = strs[i];
		int cnt = map->get(map, s);
		map->putInt(map, s, cnt+1);
	}
	printf("%s", toChars(map->toString(map)));

	freeHashMap(map);

}
