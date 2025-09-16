#include <stdio.h>
#include <stdlib.h>
#include "../lib/dsl.h"

void _dsl_grant_capacity(DSL *l);

DSL* dsl_create(void) {
    DSL* list = malloc(sizeof(DSL));
    if (list == NULL) {
        return NULL;
    }

    list->length = 0;
    list->capacity = DSL_INITIAL_CAPACITY;
    list->items = malloc(sizeof(DSL_Type) * DSL_INITIAL_CAPACITY);

    return list;
}

int dsl_destroy(DSL **l) {
    if (l == NULL || *l == NULL) {
        return -1;
    }

    free(*l);
    *l = NULL;

    return 1;
}

int dsl_is_empty(const DSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->length == 0;
}

int dsl_get_length(const DSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->length;
}

int dsl_get_capacity(const DSL *l) {
    if (l == NULL) {
        return -1;
    }

    return l->capacity;
}

int dsl_push(DSL *l, DSL_Type item) {
    if (l == NULL) {
        return -1;
    }

    _dsl_grant_capacity(l);

    l->items[l->length] = item;
    l->length++;

    return 1;
}

int dsl_insert(DSL *l, unsigned pos, DSL_Type item) {
    if (l == NULL) {
        return -1;
    }

    _dsl_grant_capacity(l);

    for (unsigned i = l->length; i > pos; i--) {
        l->items[i] = l->items[i - 1];
    }

    l->items[pos] = item;
    l->length++;

    return 1;
}

int dsl_remove(DSL *l, unsigned pos, DSL_Type* removed) {
    if (l == NULL) {
        return -1;
    }

    if (pos >= l->length) {
        return -1;
    }

    *removed = l->items[pos];

    for (unsigned i = pos; i < l->length - 1; i++) {
        l->items[i] = l->items[i + 1];
    }

    l->length--;

    return 1;
}

int dsl_seek(DSL *l, unsigned pos, DSL_Type* item) {
    if (l == NULL) {
        return -1;
    }

    if (pos >= l->length) {
        return -1;
    }

    *item = l->items[pos];

    return 1;
}

int dsl_search(DSL *l, DSL_Type item, unsigned* pos) {
    if (l == NULL) {
        return -1;
    }

    for (unsigned i = 0; i < l->length; i++) {
        if (l->items[i] == item) {
            *pos = i;
            return 1;
        }
    }

    *pos = -1;
    return 1;

}

int dsl_clear(DSL *l) {
    if (l == NULL) {
        return -1;
    }

    l->length = 0;
    return 1;

}

int dsl_print(const DSL *l) {
    if (l == NULL) {
        return -1;
    }

    if (l->length == 0) {
        printf("[]\n");
        return 1;
    }

    printf("[%d", l->items[0]);
    for (unsigned i = 1; i < l->length; i++) {
        printf(", %d", l->items[i]);
    }
    printf("]\n");

    return 1;
}

void _dsl_grant_capacity(DSL *l) {
    if (l->length < l->capacity) {
        return;
    }

    l->capacity *= 2;
    l->items = realloc(l->items, l->capacity);
}
