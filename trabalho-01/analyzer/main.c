#include <stdio.h>
#include <stdlib.h>
#include "../lib/analysis.h"

#define OP_INVERT 1 
#define OP_SEQ_SEARCH 2 
#define OP_BIN_SEARCH 3 
#define OP_REC_BIN_SEARCH 4 

void show_menu(char* filename);

int main(int argc, char* argv[]) {
    if (argc != 2) {
        show_menu(argv[0]);
        return 1;
    }

    int op = *argv[1] - '0';

    switch (op) {
        case OP_INVERT:
            analysis_invert();
            break;
        case OP_SEQ_SEARCH:
            analysis_ss();
            break;
        case OP_BIN_SEARCH:
            analysis_bs();
            break;
        case OP_REC_BIN_SEARCH:
            analysis_rbs();
            break;
        default:
            printf("Invalid option '%d'\n\n", op);
            show_menu(argv[0]);
            break;
    }

    return 0;
}

void show_menu(char* filename) {
    printf("Usage: %s <option>\n", filename);
    printf("Where <option> can be:\n");
    printf("\t1. invert\n");
    printf("\t2. sequential search\n");
    printf("\t3. binary hearch\n");
    printf("\t4. recursive binary search\n");
}

