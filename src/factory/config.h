struct CacheConfig {
    const int nsets;
    int bsize;
    int assoc;

    CacheConfig(int nsets, int bsize, int assoc) : nsets(nsets), bsize(bsize), assoc(assoc) {}  
};
