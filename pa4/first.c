#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//counters
int noPrefetchReads = 0;
int noPrefetchWrites = 0;
int prefetchReads = 0;
int prefetchWrites = 0;
int hits = 0;
int miss = 0;

size_t getSetIndex(size_t address, int numBlockBits, int numSetBits){
  //have to convert log2(numSetBits) to size_t without casting
  //return (address >> numBlockBits)%(size_t)log2(numSetBits);
  return (address>>numBlockBits)&((1<<numSetBits)-1);
}

size_t getTag(size_t address, int numBlockBits, int numSetBits){
  return address >> (numBlockBits+numSetBits);
}

int getNumSets(int cache_size, int block_size, char* associativity){
  if(strcmp(associativity, "direct") == 0){
    return cache_size/block_size;
  }
  if(strcmp(associativity, "assoc") == 0){
    return 1;
  }
  size_t length = strlen(associativity);
  char n[length-6];
  for(int i = 6; i < length; i++){
    n[i-6] = associativity[i];
  }
  return cache_size/(block_size*atoi(n));
}

int getAssoc(int cache_size, int block_size, char* associativity){
  if(strcmp(associativity, "direct") == 0){
    return 1;
  }
  if(strcmp(associativity, "assoc") == 0){
    return cache_size/block_size;
  }
  size_t length = strlen(associativity);
  char n[length-6];
  for(int i = 6; i < length; i++){
    n[i-6] = associativity[i];
  }
  return atoi(n);
}

bool isPowerOf2(int i){
  return (i != 0 && (i & (i-1)) == 0);
}

bool isValid(int cache_size, int block_size, char * cache_policy, char * associativity, int prefetch_size){ //returns false if any of the inputs are invalid
  if(!isPowerOf2(cache_size)){
    printf("error: cache size is not a power of 2");
    return false;
  }
  if(!isPowerOf2(block_size)){
    printf("error: block size is not a power of 2");
    return false;
  }
  if(strcmp(cache_policy, "fifo") != 0 && strcmp(cache_policy,"lru") != 0){
    printf("error: invalid cache policy");
    return false;
  }
  //check associativity is valid
  if(prefetch_size <= 0){
    printf("error: invalid prefetch size");
    return false;
  }
  return true;
}

bool isInCache(size_t** cache, size_t address, int numBlockOffBits, int numSetBits, int numBlocks){
  size_t setIndex = getSetIndex(address, numBlockOffBits, numSetBits);
  size_t tag = getTag(address, numBlockOffBits, numSetBits);
  for(int i = 0; i < numBlocks; i++){
    if(cache[setIndex][i] == tag){
      return true;
    }else if(cache[setIndex][i] == (size_t)NULL){
      return false;
    }
  }
  return false;
}

size_t** insert(size_t** cache, size_t address, int numBlockOffBits, int numSetBits, int numBlocks){
  size_t setIndex = getSetIndex(address, numBlockOffBits, numSetBits);
  size_t tag = getTag(address, numBlockOffBits, numSetBits);
  bool inserted = false;
  for(int i = 0; i < numBlocks; i++){
    if(cache[setIndex][i] == (size_t)NULL){
      cache[setIndex][i] = tag;
      inserted = true;
      break;
    }
  }
  if(!inserted){ //this means that the set is full
    //shift everything one left
    for(int i = 1; i < numBlocks; i++){
      cache[setIndex][i-1] = cache[setIndex][i];
    }
    cache[setIndex][numBlocks-1] = tag;
  }
  return cache;

}

void noPrefetch(FILE * trace_file, size_t** cache, int numBlockOffBits, int numSetBits, int numBlocks){
  char action;
  size_t address;
  while(fscanf(trace_file,"%c %zx\n", &action, &address) != EOF){
    if(action == '#') break;
    if(action == 'W') noPrefetchWrites++;
    if(isInCache(cache, address, numBlockOffBits, numSetBits, numBlocks)){
      hits++;
    }else{
      miss++;
      noPrefetchReads++;
      cache = insert(cache, address, numBlockOffBits, numSetBits, numBlocks);
    }
  }
  return;
}

void prefetch(FILE * trace_file, size_t** cache, int numBlockOffBits, int numSetBits, int numBlocks, int prefetch_size){
  char action;
  size_t address;
  while(fscanf(trace_file,"%c %zx\n", &action, &address) != EOF){
    if(action == '#') break;
    if(action == 'W') prefetchWrites++;
    if(isInCache(cache, address, numBlockOffBits, numSetBits, numBlocks)){
    }else{
      prefetchReads++;
      cache = insert(cache, address, numBlockOffBits, numSetBits, numBlocks);
    }
  }
  return;
}

int main(int argc, char *argv[]){
  if(argc != 7){
    printf("error: invalid number of arguments");
    return 0;
  }
  int cache_size = atoi(argv[1]);
  int block_size = atoi(argv[2]);
  char* cache_policy = argv[3]; //FIFO or LRU
  char* associativity = argv[4];
  int prefetch_size = atoi(argv[5]); //number of blocks to move to memory in case of miss

  if(!isValid(cache_size, block_size, cache_policy, associativity, prefetch_size)){
    return 0;
  }

  int numSets = getNumSets(cache_size, block_size, associativity);
  int numBlocks = cache_size/(numSets*block_size);
  int numBlockOffBits = log2(block_size);
  int numSetBits = log2(numSets);
  int assoc = getAssoc(cache_size, block_size, associativity);

  size_t** cache =(size_t**)malloc(numSets*sizeof(size_t*)); //each row is a set
  for(int i = 0; i < numSets; i++){
    cache[i] = (size_t*)malloc(numBlocks*sizeof(size_t)); //each column is a block
    for(int j = 0; j < numBlocks; j++){
      cache[i][j] = (size_t)NULL;
    }
  }

  FILE * trace_file = fopen(argv[6], "r");
  if(trace_file==NULL){ //file not found
    printf("error: file not found");
    return 0;
  }

  noPrefetch(trace_file, cache, numBlockOffBits, numSetBits, numBlocks);

  //resetting cache for prefetch
  for(int i = 0; i < numSets; i++){
    for(int j = 0; j < numBlocks; j++){
      cache[i][j] = (size_t)NULL;
    }
  }

  //moving file pointer back to the top of the file
  rewind(trace_file);

  //no prefetch
  printf("no-prefetch\n");
  printf("Memory reads: %d\n",noPrefetchReads);
  printf("Memory writes: %d\n",noPrefetchWrites);
  printf("Cache hits: %d\n",hits);
  printf("Cache misses: %d\n",miss);

  //prefetch
  printf("with-prefetch\n");
  printf("Memory reads: %d\n",prefetchReads);
  printf("Memory writes: %d\n",prefetchWrites);
  printf("Cache hits: %d\n",hits);
  printf("Cache misses: %d\n",miss);

  //freeing cache
  for(int i = 0; i < numSets; i++){
    for(int j = 0; j < numBlocks; j++){
      free(cache[i][j]);
    }
  }

  return 0;
}
