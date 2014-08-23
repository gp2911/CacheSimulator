
#define LRU 0
#define LFU 1
#define RR 2

#include <cstdint>

class Cache{
  protected:
    int size;
    int assoc;
    int blk_size;
    int hit_latency;
    int policy;
  
    int num_blocks;
    int map_bits;
    int set_bits;
    
    //MemAddrs stored in cache
    uint64_t** addrs_stored;
     
    //Stats
    int accesses;
    int hits;
    int miss_ratio;
    
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
    virtual void evict(int block);
    
    /**
     * Check if given line is isInvalid
     * @param block : Block to check
     * @param set   : Set to check
     * @return : true if valid, false if not
     */
    bool is_valid(int block, int set);
    
    /**
     * Invalidate the given block
     * @param block : Block in which reqd entry resides
     * @param set   : Set to invalidate
     */
    void invalidate(int block, int set);
    
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