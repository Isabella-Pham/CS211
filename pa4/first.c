#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

//counters
int mem_reads = 0;
int mem_writes = 0;
int cache_hits = 0;
int cache_miss = 0;

typedef struct block{
    size_t tag;
    size_t valid;
}block;

size_t getBlockOffset(size_t address, int blockOffset){
  return address >> blockOffset;
}

size_t getSetIndex(size_t address, int blockOffset, int numSets){
  return (address >> blockOffset)%numSets;
}

size_t getTagIndex(size_t address, int blockOffset, int setIndex){
  return address >> (blockOffset+setIndex);
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
  return c/(b*atoi(n));
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
  return (i != 0 && (c & (c-1) == 0));
}

bool isValid(int cache_size, int block_size, char * cache_policy, char * associativity, int prefetch_size){ //returns false if any of the inputs are invalid
  if(!isPowerof2(cache_size)){
    printf("error: cache size is not a power of 2");
    return false;
  }
  if(!isPowerof2(block_size)){
    printf("error: block size is not a power of 2");
    return false;
  }
  if(strcmp(cache_policy, "fifo") != 0 || strcmp(cache_policy,"lru") != 0){
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

  block** cache =(block**)malloc(numSets*sizeof(block*)); //each row is a set
  for(int i = 0; i < numSets; i++){
    cache[i] = (block*)malloc(numBlocks*sizeof(block)); //each column is a block
  }

  FILE * trace_file = fopen(argv[6], "r");
  if(f==NULL){ //file not found
    printf("error: file not found");
    return 0;
  }
}
