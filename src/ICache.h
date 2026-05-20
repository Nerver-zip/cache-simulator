#pragma once

#include "factory/config.h"
#include <vector>
#include <string>
#include "decoder/instruction.h"

class ICache {
public:
    virtual long long getTotal() const = 0;

    virtual long long getHits() const = 0;

    virtual long long getMisses() const = 0;

    double getHitRate() const {
        return getTotal() == 0 ? 0.0 : static_cast<double>(getHits()) / getTotal();
    }

    double getMissRate() const {
        return 1 - getHitRate();
    }
    
    virtual void run() = 0;
    
    virtual ~ICache() = default;

protected:
    long long total;
    long long hits;
    long long misses;
};
