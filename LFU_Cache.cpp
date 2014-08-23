#include "LFU_Cache.h"
#include <cstdlib>

LFU_Cache::LFU_Cache(int size, int assoc, int blk_size, int hit_latency): Cache(size, assoc, blk_size, hit_latency, hit_latency)
{
  //initialise frequency_matrix
  this->frequency_matrix = (int**)malloc(num_blocks * sizeof(int*));
  for(int i = 0; i < num_blocks; i++){
    this->frequency_matrix[i] = (int*) malloc(assoc * sizeof(int));
  }
  
  //initialise all entries in last_use_matrix to -1 (not used at all so far)
  for(int i = 0; i < num_blocks; i++){
    for(int j = 0; j < assoc; j++){
      this->frequency_matrix[i][j] = 0;
    }
  }
}

void LFU_Cache::evict(int block)
{
  int victim = 0;
  
  for(int i = 0; i < assoc; i++){
    if(frequency_matrix[block][i] < victim)
      victim = i;
  }
  
  invalidate(block, victim);
  
  curr_block = block;
  curr_set = victim;
  
}

void LFU_Cache::read(uint64_t address)
{
  Cache::read(address);
  if(hit)
    frequency_matrix[curr_block][curr_set]++;
  else
    frequency_matrix[curr_block][curr_set] = 0;
}

void LFU_Cache::write(uint64_t address)
{
  Cache::write(address);
  if(hit)
    frequency_matrix[curr_block][curr_set]++;
  else
    frequency_matrix[curr_block][curr_set] = 0;
}
