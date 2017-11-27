#include <stdio.h>
#include <stdlib.h>
 
#include "Object.h"
#include "stc.h"
#include "List.h"
#include "Stack.h"
#include "Vector.h"
#include "HashMap.h"
#include "Process.h"
#include "sysser.h"
#include "String.h"
#include "BigNumber.h"

void testProcess(){
	char buf[255];
	int size = 0;
	Process *process = newProcess();
	process->start(process, "test");
	int n = 0 ;

	while ( (n = process->readline(process, buf, 122)) > 0){
		buf[n] = '\0';
		printf(buf);
	}
	freeProcess(process);
}

void testHashMap(){
	HashMap *map = newHashMap(NULL);

	map->put(map, "name", "lsj");
	map->put(map, "id", "2015200563");
	map->put(map, "age", "24");
	

	Vector *keys = map->keys(map);
	for (int i = 0; i < keys->size(keys); i++){
		char *key = keys->get(keys, i);
		printf("%s:%s\n", key, map->get(map, key));
	}
	freeVector(keys);

	map->put(map, "age", "25");

	printf("\n\n");
	Vector *entries = map->entries(map);
	for (int i = 0; i < entries->size(entries); i++){
		Entry *entry = entries->get(entries, i);
		printf("%s:%s\n", entry->key, entry->value);
	}

	freeVector(entries);
	freeHashMap(map);
}

void testVector(){
	Vector *vector = newVector();
	vector->add(vector, 1);
	vector->add(vector, 2);
	vector->add(vector, 3);
	vector->add(vector, 4);
	vector->add(vector, 5);

	for (int i = 0; i < vector->size(vector); i++){
		printf("%d ", vector->get(vector, i));
	}

	vector->remove(vector, 0);
	vector->remove(vector, 1);
	printf("\n");
	for (int i = 0; i < vector->size(vector); i++){
		printf("%d ", vector->get(vector, i));
	}

	vector->insert(vector, 2, 100);
	printf("\n");
	for (int i = 0; i < vector->size(vector); i++){
		printf("%d ", vector->get(vector, i));
	}
}

void testString(){
	String *s = newString("");
	s->append(s, "abcdefghijklmn");
	s->appendInt(s, 123);
	s->appendFloat(s, 1.23);
	s->appendPtr(s, s);
	printf("%s", s->toChars(s));
	freeString(s);
}

int main(){
	testSTC();
	//testHashMap();
	//testString();
	while (1);
}