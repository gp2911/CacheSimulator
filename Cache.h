
#define LRU 0
#define LFU 1
#define RR 2

//#include <cstdint>
#include <stdint.h>

class Cache{
  protected:
    int size; // Total size of cache (Units ? In KBs)
    int assoc; // Associativity - no. of blocks in a set.
    int blk_size; // Size of a memory block.
    int hit_latency; // Time to access an address
    int policy; // Replacement policy 
  
    int num_sets; // Actually number of sets
    int map_bits; // Number of bits for map part (middle)
    int set_bits;  // Not required I think
    int offset_bits; // Number of bits 
    
    //MemAddrs stored in cache
    uint64_t** addrs_stored;  // Matrix of size num_sets x assoc
     
    //Stats
    int accesses;
    int hits;
    int miss_ratio;
    
    //Current Task status : hit/miss and block, set queried
    bool hit;
    int curr_block;
    int curr_set;
    
    //Functions
    /**
     * Find block from the given address
     * 
     * @param address : Address to be accessed
     * @return : Block corresponding to the address
     */
    int find_block(uint64_t address);
    
    /**
     * Find set from the given address
     * @param address : Address to be accessed
     * @return : Set corresponding to the address
     */
    int find_set(uint64_t address);
    
    /**
     * Search for a given tag (linear searching)
     * @param block : block to search in
     * @param tag   : tag to search for
     * @return	: true if found, false if not found
     */
    bool search(int block, uint64_t tag);
    
    /**
     * Evict a block from the given find_set
     * @param block : Block to evict from
     */
    virtual void evict(int set);
    
    /**
     * Check if given line is isInvalid
     * @param block : Block to check
     * @param set   : Set to check
     * @return : true if valid, false if not
     */
    bool is_valid(int set, int block);
    
    /**
     * Invalidate the given block
     * @param set : Set in which block is present.
     * @param block   : Block to invalidate 
     */
    void invalidate(int set, int block);
    
  public:
    Cache(int size, int assoc, int blk_size, int hit_latency, int policy);
    
    /**
     * Read access to an address.
     * @param address : Address to be read
     */
    void read(uint64_t address);
    
    /**
     * Write access to address.
     * @param address : Address to be written
     * */
    void write(uint64_t address);
};