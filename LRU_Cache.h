/* LRU_Cache.cpp
 * Class to model LRU_Cache
 */

#include "Cache.h"

class LRU_Cache : public Cache{
  public:
    LRU_Cache(int size, int assoc, int blk_size, int hit_latency) : Cache(size, assoc, blk_size, hit_latency, LRU){
      //Nothing to do
    }
};
    