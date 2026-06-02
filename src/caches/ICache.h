#pragma once

#include <vector>
#include <string>

class ICache {
protected:
    long long hits;
    
    struct Miss {
        long long total;
        long long compulsory;
        long long conflict;
        long long capacity;
        Miss() : total(0), compulsory(0), conflict(0), capacity(0) {}
    };

    Miss misses;

public:
    ICache() : hits(0), misses() {}

    long long getTotal() const {
        return hits + misses.total;
    }

    long long getHits() const {
        return hits;
    }

    Miss getMisses() const {
        return misses;
    }

    double getHitRate() const {
        return getTotal() == 0 ? 0.0 : static_cast<double>(hits) / getTotal();
    }

    double getMissRate() const {
        return 1.0 - getHitRate();
    }

    double getCompulsoryMissRate() const {
        return static_cast<double>(misses.compulsory) / misses.total;
    }

    double getConflictMissRate() const {
        return static_cast<double>(misses.conflict) / misses.total;
    }
    
    double getCapacityMissRate() const {
        return static_cast<double>(misses.capacity) / misses.total;
    }

    virtual bool execute(int index, int tag) = 0;
    
    virtual ~ICache() = default;
};

struct CacheConfig {
    int nsets;
    int assoc;
    int bsize;

    constexpr CacheConfig(int nsets, int assoc, int bsize) : nsets(nsets), assoc(assoc), bsize(bsize) {}  
};
