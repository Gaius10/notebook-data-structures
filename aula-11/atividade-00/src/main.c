#include <stdio.h>
#include "../lib/queue.h"

int main() {
    Queue* q = create_queue();
    int buffer;

    insert(q, 1);
    insert(q, 2);
    insert(q, 3);

    print_queue(q);

    shift(q, &buffer);
    printf("Shifted: %d\n", buffer);
    print_queue(q);

    free_queue(&q);
    return 0;
}

