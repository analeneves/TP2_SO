typedef struct {
    int last_access;
    int altered;
    int present_absent;
    unsigned offset;
} Input;

typedef struct item_arq {
    int chave;
    Input* valor;
    struct item_arq *next;
} Item_arq;

typedef struct {
    int size;
    int count;
    Item_arq ** item_arq;
} Table;

typedef struct {
    unsigned offset;
} Value_queue;

typedef struct {
    int size;
    int last;
    int first;
    int count;
    Value_queue * values;
} Queue;


Item_arq * additem(unsigned *a, Input *in);
Table * newtable(int *size);
void deleteitem(Item_arq *j);
void deletetable(Table *t_hash);
Queue *newQueue(int *size);
Value_queue *newvalue();
void insert(Queue *n, Value_queue *a);
void remove(Queue *n);
void deletequeue(Queue *n);