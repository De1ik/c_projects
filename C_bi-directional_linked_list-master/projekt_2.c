//Delikatnyi Artem
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct id_mer{
    char big_lett;
    char id_figure[4];
    char small_lett;
} ID_MER;


typedef struct pos_mod{
    char latitude[9];
    char longtitude[9];
} POS_MOD;


typedef struct records{
    struct records* next;
    struct records* previous;
    ID_MER id;
    POS_MOD pos;
    char type[3];
    double hodnota;
    char time[5];
    char date[9];
} RECORDS;



void func_n(FILE **fr, RECORDS **start, RECORDS **end, int *size){
    //free current linked list
    if (*size > 0){
        RECORDS *current = *start;
        while (1){
            if (current->next != NULL){
                current = current->next;
                free(current->previous);
            }
            else{
                free(current);
                *start = NULL;
                *end = NULL;
                break;
            }
        }
    }

    //if we can not open the file
    if((*fr == NULL) && (*fr = fopen("dataloger_V2.txt", "r")) == NULL){
        printf("Zaznamy neboli nacitane!\n");
    }
    //created link list
    else{
        *size = 0;
        char buffer[50];

        RECORDS *prev_rec = NULL;
        while (!feof(*fr)){
            RECORDS *current = (RECORDS*) malloc(sizeof(RECORDS));
            if((!feof(*fr) && (fgets(buffer, sizeof(buffer), *fr)) != NULL)){
                (*size)++;
                if (*size == 1){
                    *start = current;
                    current->previous = NULL;
                    current->next = NULL;
                }
                else{
                    prev_rec->next = current;
                    current->previous = prev_rec;
                    current->next = NULL;
                }

                //set id in small letter, big letter and numbers
                fgets(buffer, sizeof(buffer), *fr);


                current->id.big_lett = buffer[0];
                current->id.small_lett = buffer[4];
                strncpy(current->id.id_figure, buffer+1, 3);
                current->id.id_figure[3] = '\0';
                //---------------------------------------


                //set position lattitude and longtitude
                fgets(buffer, sizeof(buffer), *fr);

                strncpy(current->pos.latitude, buffer, 8);
                current->pos.latitude[8] = '\0';
                strncpy(current->pos.longtitude, buffer+8, 8);
                current->pos.longtitude[8] = '\0';
                //--------------------------------


                // set type
                fgets(buffer, sizeof(buffer), *fr);

                strncpy(current->type, buffer, 2);
                current->type[2] = '\0';
                //---------------------------------


                //set hodnota
                fgets(buffer, sizeof(buffer), *fr);
                current->hodnota = atof(buffer);
                //-----------------------------------


                //set time
                fgets(buffer, sizeof(buffer), *fr);

                strncpy(current->time, buffer, 4);
                current->time[4] = '\0';
                //-----------------------------------


                //set date
                fgets(buffer, sizeof(buffer), *fr);
                strncpy(current->date, buffer, 8);
                current->date[8] = '\0';
                //------------------------------------

                //set current node as the previous
                prev_rec = current;
            }
        }
        //the end will be the last node
        *end = prev_rec;
        rewind(*fr);


        printf("Nacitalo sa %d zaznamov\n", *size);
    }

}


void func_v(RECORDS *start) {
    int counter = 0;
    if (start != NULL) {
        RECORDS *current = start;
        while (current != NULL){
            counter++;
            printf("%d:\n", counter);
            printf("ID: %c%s%c \t %s\t%g\n", current->id.big_lett, current->id.id_figure, current->id.small_lett, current->type, current->hodnota);
            printf("Poz: %s\t%s\n", current->pos.latitude, current->pos.longtitude);
            printf("DaC: %s\t%s\n", current->date, current->time);

            current = current->next;
        }
    }
    else{
        printf("spojeny zoznam nebol vytvoreny\n");
    }
}



void func_p(RECORDS **start, RECORDS **end, int *size){
    int index;
    char new_id[6], pos[18], type[3], time[5], date[9];
    double hodnota;
    scanf("%d", &index);
    if (index > 0) {


        scanf("%s", new_id);
        scanf("%s", pos);
        scanf("%s", type);
        scanf("%lf", &hodnota);
        scanf("%s", time);
        scanf("%s", date);


        RECORDS *new_record = (RECORDS *) malloc(sizeof(RECORDS));
        if (*start == NULL) {
            *start = new_record;
            *end = new_record;
            new_record->next = NULL;
            new_record->previous = NULL;
        } else if (index > *size) {
            RECORDS *last = *end;
            last->next = new_record;
            new_record->previous = last;
            new_record->next = NULL;
            *end = new_record;
        } else {

            int counter = 1;
            RECORDS *previous_one = NULL, *current = *start;
            while (counter != index) {
                current = current->next;
                counter++;
                printf("counter ++\n");
            }
            if (current != *start){
                previous_one = current->previous;
                printf("WORKING NULL\n");
                previous_one->next = new_record;
                new_record->previous = previous_one;
            }
            else{
                new_record->previous = NULL;
                *start = new_record;
            }
            current->previous = new_record;
            new_record->next = current;
        }


        // set new id
        new_record->id.big_lett = new_id[0];
        new_record->id.small_lett = new_id[4];
        strncpy(new_record->id.id_figure, new_id + 1, 3);
        new_record->id.id_figure[3] = '\0';

        //set new position;

        strncpy(new_record->pos.latitude, pos, 8);
        new_record->pos.latitude[8] = '\0';

        strncpy(new_record->pos.longtitude, pos + 8, 8);
        new_record->pos.longtitude[8] = '\0';

        //set hodnota
        new_record->hodnota = hodnota;

        // set type
        strncpy(new_record->type, type, 2);
        new_record->type[2] = '\0';

        //set time
        strncpy(new_record->time, time, 4);
        new_record->time[4] = '\0';

        //set date
        strncpy(new_record->date, date, 8);
        new_record->date[8] = '\0';

        (*size)++;
    }
    else{
        printf("index must be > 0\n");
    }
}


void func_z(RECORDS **start, RECORDS **end, int *size){
    if (*start == NULL){
        printf("Spojeny zoznam nebol vytvoreny.\n");
    }
    else{
        char find_id[6];
        int data_check = 1;
        char cur_id[5];
        scanf("%s", find_id);
        find_id[5] = '\0';

        RECORDS *current = *start;
        while (current != NULL){

            cur_id[0] = current->id.big_lett;
            strncpy(cur_id+1, current->id.id_figure, 3);
            cur_id[4] = current->id.small_lett;

            if (strncmp(cur_id, find_id, 5) == 0){
                data_check = 0;
                (*size)--;
                printf("Zaznam pre ID: %s bol vymazany.\n", find_id);

                if (current->previous == NULL){
                    if (current->next == NULL){
                        free(current);
                        *start = NULL;
                        *end = NULL;
                        break;
                    }
                    else{
                        *start = current->next;
                        free(current);
                        current = *start;
                        current->previous = NULL;
                        continue;
                    }
                }
                else if(current->next == NULL) {
                    current = current->previous;
                    *end = current;
                    free(current->next);
                    current->next = NULL;
                    break;
                }
                else{
                    RECORDS *previous_one = current->previous;
                    RECORDS *next_one = current->next;
                    previous_one->next = next_one;
                    next_one->previous = previous_one;
                    free(current);
                    current = next_one;
                    continue;
                }
            }
            current = current->next;

        }
        if (data_check == 1){
            printf("Id sa nenaslo\n");
        }
        else if (*size == 0){
            printf("Vsetky zaznamy boli vymazane -> spojeny zaznam bol vymazany.\n");
        }
    }
}


void func_u(RECORDS **start, RECORDS **end, int size){
    RECORDS *current;
    int cur_date_1, cur_date_2, cur_time_1, cur_time_2;

    if (size > 1) {
        for (int i = 0; i < size; i++) {
            current = *start;
            for (int j = 0; j < size - i - 1; j++) {
                cur_date_1 = atoi(current->date);
                cur_time_1 = atoi(current->time);
                cur_date_2 = atoi(current->next->date);
                cur_time_2 = atoi(current->next->time);

                if (cur_date_2 > cur_date_1 || ((cur_date_2 == cur_date_1) && (cur_time_2 > cur_time_1))) {

                    RECORDS *next_one = current->next;
                    if (j == 0){
                        RECORDS *after_next_one = next_one->next;

                        after_next_one->previous = current;

                        current->next = after_next_one;
                        current->previous = next_one;

                        next_one->next = current;
                        next_one->previous = NULL;

                        *start = next_one;
                    }
                    else if(j == size-2){
                        current->previous->next = next_one;

                        next_one->previous = current->previous;
                        next_one->next = current;

                        current->next = NULL;
                        current->previous = next_one;

                        *end = current;
                    }
                    else {
                        RECORDS *prev = current->previous;
                        RECORDS *after_next_one = next_one->next;

                        current->next = after_next_one;
                        current->previous = next_one;

                        next_one->previous = prev;
                        next_one->next = current;

                        prev->next = next_one;
                        after_next_one->previous = current;
                    }

                }
                else{
                    current = current->next;
                }
            }
        }
        printf("Spajany zoznam bol usporiadany.\n");
    }
    else if (size < 1){
        printf("Chyba usporiadania alebo spojeny zoznam nebol vytvoreny.\n");
    }
    else{
        printf("Spajany zoznam bol usporiadany.\n");
    }
}


void func_r(RECORDS **start, RECORDS **end, int size){
    if (*start == NULL){
        printf("spojeny zoznam nebol vytvoreny\n");
    }
    else {
        int ind_1, ind_2;
        scanf("%d %d", &ind_1, &ind_2);

        if (ind_1 > 0 & ind_2 > 0 & ind_1 <= size & ind_2 <= size & ind_1 != ind_2) {
            int min_ind, max_ind, counter = 1;
            if (ind_1 > ind_2) {
                min_ind = ind_2;
                max_ind = ind_1;
            } else {
                min_ind = ind_1;
                max_ind = ind_2;
            }

            RECORDS *cur_1 = *start, *cur_2 = *start;

            while (counter != min_ind) {
                cur_1 = cur_1->next;
                cur_2 = cur_2->next;

                counter++;
            }
            while (counter != max_ind) {
                cur_2 = cur_2->next;

                counter++;
            }


            if (min_ind + 1 == max_ind) {
                RECORDS *before_cur_1 = cur_1->previous;
                RECORDS *after_cur_2 = cur_2->next;

                cur_1->next = after_cur_2;
                cur_1->previous = cur_2;

                cur_2->next = cur_1;
                cur_2->previous = before_cur_1;

                if (before_cur_1 != NULL) {
                    before_cur_1->next = cur_2;
                } else {
                    *start = cur_2;
                }
                if (after_cur_2 != NULL) {
                    after_cur_2->previous = cur_1;
                } else {
                    *end = cur_1;
                }
            } else {
                RECORDS *after_cur_1 = cur_1->next;
                RECORDS *before_cur_1 = cur_1->previous;
                RECORDS *after_cur_2 = cur_2->next;
                RECORDS *before_cur_2 = cur_2->previous;

                cur_1->next = after_cur_2;
                cur_1->previous = before_cur_2;
                cur_2->next = after_cur_1;
                cur_2->previous = before_cur_1;

                after_cur_1->previous = cur_2;
                before_cur_2->next = cur_1;

                if (before_cur_1 != NULL)
                    before_cur_1->next = cur_2;
                else
                    *start = cur_2;
                if (after_cur_2 != NULL)
                    after_cur_2->previous = cur_1;
                else
                    *end = cur_1;
            }
        }
    }
}


void func_k(RECORDS **start, RECORDS **end, int size){
    if (size > 0){
        RECORDS *current = *start;
        while (1){
            if (current->next != NULL){
                current = current->next;
                free(current->previous);
            }
            else{
                free(current);
                *start = NULL;
                *end = NULL;
                break;
            }
        }
    }
}




int main() {
    FILE *f = NULL;
    int size = 0;
    RECORDS *start = NULL;
    RECORDS *end = NULL;

    char sign = 'x';

    do {
        scanf("%c", &sign);
        switch (sign) {
            case 'n':
                func_n(&f, &start, &end, &size);
                break;
            case 'v':
                func_v(start);
                break;
            case 'p':
                 func_p(&start, &end, &size);
                 break;
            case 'z':
                 func_z(&start, &end, &size);
                 break;
            case 'u':
                 func_u(&start, &end, size);
                 break;
            case 'r':
                 func_r(&start, &end, size);
                 break;
        }
    }while (sign != 'k');
    func_k(&start, &end, size);

    return 0;
}
