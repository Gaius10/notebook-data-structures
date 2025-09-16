
#ifndef DSL_H
#define DSL_H

#define DSL_INITIAL_CAPACITY 4

typedef int DSL_Type;
typedef struct {
    DSL_Type *items;
    unsigned length;
    unsigned capacity;
} DSL;

DSL* dsl_create(void);
int dsl_destroy(DSL **l);

int dsl_is_empty(const DSL *l);
int dsl_get_length(const DSL *l);
int dsl_get_capacity(const DSL *l);

int dsl_push(DSL *l, DSL_Type item);
int dsl_insert(DSL *l, unsigned pos, DSL_Type item);
int dsl_remove(DSL *l, unsigned pos, DSL_Type* removed);

int dsl_seek(DSL *l, unsigned pos, DSL_Type* item);
int dsl_search(DSL *l, DSL_Type item, unsigned* pos);

int dsl_clear(DSL *l);
int dsl_print(const DSL *l);

#endif

