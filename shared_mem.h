#define SIZE 3
struct shared_use_st {
    bool busy;
    int count;
    int M[SIZE][SIZE];
    int L[SIZE];
    int D[SIZE];
};
