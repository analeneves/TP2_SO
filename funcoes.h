typedef struct {
    int last_access;
    int altered;
    int pres_absent_pages;
    int referenced_pages;
} Input;

typedef struct item_arq {
    int *chave;
    Input *valor;
    struct item_arq *next;
} Item_arq;

typedef struct {
    int size;
    int count;
    Item_arq **item_arqs;
} Table;
//**********************************************//
typedef struct {
    unsigned int offset;
} Value_queue;

typedef struct {
    int size;
    int last;
    int first;
    int count;
    Value_queue * values;
} Queue;


Item_arq * additem(unsigned int *a, Input *in);
Table * newtable(int *size);
void deleteitem(Item_arq *j);
void deletetable(Table *t_hash);

//************************************************8
Queue *newQueue(int *size);
Value_queue *newvaluequeue();
void insert(Queue *n, Value_queue *a);
void removeQueue(Queue *n);
void deletequeue(Queue *n);