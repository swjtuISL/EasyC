#include <stdlib.h>
#include <string.h>

#include "HashMap.h"

static const INITIAL_BUCKETS_LENGTH = 16;
static const DEFAULT_MAX_AVERAGE_DEEP = 3;

static void * get(HashMap *self, void *key);
static void * put(HashMap *self, void *key, void * value);
static int size(HashMap *self);
static Vector *keys(HashMap *self);
static Vector *entries(HashMap *self);
static void resize(HashMap *self);
static unsigned long defaultHash(void *obj);		// key的默认hash处理函数

HashMap *newHashMap( 
	unsigned long (* hashFunction)(void *obj)		// 配置hash函数
	){
	HashMap *map = (HashMap *)malloc(sizeof(HashMap));

	map->_buckets = (KVNode **)malloc(sizeof(KVNode *)*INITIAL_BUCKETS_LENGTH);
	for (int i = 0; i < INITIAL_BUCKETS_LENGTH; i++){
		map->_buckets[i] = NULL;
	}
	map->_size = 0;
	map->_bucketsLength = INITIAL_BUCKETS_LENGTH;
	map->_maxAverageDeep = DEFAULT_MAX_AVERAGE_DEEP;

	// load function
	map->get = get;
	map->put = put;
	map->size = size;
	map->keys = keys;
	map->entries = entries;
	map->_resize = resize;

	map->_hash = hashFunction == NULL ? defaultHash : hashFunction;

	return map;
}

void removeHashMap(HashMap *map){
	for (int i = 0; i < map->_bucketsLength; i++){
		KVNode *node = map->_buckets[i];
		while (node!=NULL && node->next != NULL){			// 释放桶中链表
			KVNode *nextnode = node->next;
			free(node);
			node = nextnode;
		}
		free(node);
		map->_buckets[i] = NULL;
	}
	free(map->_buckets);
	map->_buckets = NULL;
	free(map);
}

static void * get(HashMap *self, void *key){
	int idx = self->_hash(key) % self->_bucketsLength;

	for (KVNode *node = self->_buckets[idx]; node != NULL; node = node->next){
		if (strcmp(node->key, key)==0){
			return node->value;
		}
	}

	return NULL;
}

/*

*/
static void * put(HashMap *self, void *key, void * value){
	int idx = 0;
	KVNode *bucketop = NULL;

	self->_resize(self);			// 是否进行扩充

	idx = self->_hash(key) % self->_bucketsLength;
	bucketop = self->_buckets[idx];

	for (KVNode *node = self->_buckets[idx]; node != NULL; node = node->next){
		if (strcmp(node->key, key) == 0){	// 覆盖
			void *old = node->value;
			node->value = value;
			return old;
		}
	}

	KVNode * newnode = (KVNode *)malloc(sizeof(KVNode));
	newnode->key = key;
	newnode->value = value;
	newnode->next = bucketop;
	self->_buckets[idx] = newnode;
	self->_size += 1;
	return NULL;
}

/*

*/
static void resize(HashMap *self){
	float averageDeep = (float)(self->_size+1) / self->_bucketsLength;
	if (averageDeep < self->_maxAverageDeep){
		return ;
	}
	// 新的桶和桶大小
	int newBucketsLength = self->_bucketsLength * 2;
	KVNode **newBuckets = (KVNode **)malloc(sizeof(KVNode *)*newBucketsLength);
	for (int i = 0; i < newBucketsLength; i++){
		newBuckets = NULL;
	}
	// 旧桶节点移动到新桶
	for (int i = 0; i < self->_bucketsLength; i++){
		KVNode *tmpnode = NULL;
		for (KVNode *node = self->_buckets[i]; node != NULL; node = tmpnode->next){
			int idx = self->_hash(node->key) % newBucketsLength;
			KVNode * bucketop = newBuckets[idx];
			tmpnode = node->next;
			node->next = bucketop;
			newBuckets[idx] = node;
		}
	}
	free(self->_buckets);
	self->_buckets = newBuckets;
	self->_bucketsLength = newBucketsLength;
}


/*

*/
static int size(HashMap *self){
	return self->_size;
}

static Vector *keys(HashMap *self){
	Vector *vector = newVector();
	for (int i = 0; i < self->_bucketsLength; i++){
		for (KVNode *node = self->_buckets[i]; node != NULL; node = node->next){
			vector->add(vector, node->key);
		}
	}
	return vector;
}

static Vector *entries(HashMap *self){
	Vector *vector = newVector();
	for (int i = 0; i < self->_bucketsLength; i++){
		for (KVNode *node = self->_buckets[i]; node != NULL; node = node->next){
			Entry *entry = (Entry *)malloc(sizeof(Entry));
			entry->key = node->key;
			entry->value = node->value;
			vector->add(vector, entry);
		}
	}
	return vector;
}

static unsigned long defaultHash(void *obj){
	char *s = (char *)obj;
	unsigned long val = 0;
	for (int i = 0; s[i] != '\0'; i++){
		val += s[i];
	}
	return val;
}