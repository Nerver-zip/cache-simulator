#pragma once

#include "../decode/decoder.h"
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
    
    virtual void execute(int index, int tag) = 0;
    
    virtual ~ICache() = default;
};

struct CacheConfig {
    const int nsets;
    int bsize;
    int assoc;

    CacheConfig(int nsets, int bsize, int assoc) : nsets(nsets), bsize(bsize), assoc(assoc) {}  
};
