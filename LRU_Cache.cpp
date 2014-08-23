#include "LRU_Cache.h"

LRU_Cache::LRU_Cache(int size, int assoc, int blk_size, int hit_latency): Cache(size, assoc, blk_size, hit_latency, hit_latency)
{
  //Nothing to do
}

void LRU_Cache::evict(int block)
{
  //Evict using LRU policy
}

