#pragma once

#include <vector>
#include <string>

class ICache {
protected:
    long long total;
    long long hits;
    
    struct Miss {
        long long total;
        long long compulsory;
        long long conflict;
        long long capacity;
    };

    Miss misses;

public:
    long long getTotal() {
        return total;
    }

    long long getHits() const {
        return hits;
    }

    Miss getMisses() const {
        return misses;
    }

    double getHitRate() const {
        return total == 0 ? 0.0 : static_cast<double>(hits) / total;
    }

    double getMissRate() const {
        return 1 - getHitRate();
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
