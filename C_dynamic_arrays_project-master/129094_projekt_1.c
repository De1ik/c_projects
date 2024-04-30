#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <math.h>

 
void v_func(FILE **fr, char ***p_id, char ***p_pos, char ***p_type, char ***p_value, char ***p_time, char ***p_date, int *p_rec_numb){
    char sign;
    int amnt_rows = 6;
    char *names[] = {
        "ID. mer. modulu",
        "Pozicia modulu",
        "Typ mer. veliciny",
        "Hodnota",
        "Cas merania",
        "Datum merania"
    };

    //Ak je súbor zatvorený -> skúste ho otvoriť, ak sa to nepodarí, print "Neotvoreny subor"
    if (*fr == NULL){
        if((*fr = fopen("dataloger.txt", "r")) == NULL){
            printf("Neotvoreny subor\n");
        }
    }


    if (*fr != NULL){
        //Ak ukazovateľ neukazuje na NULL, znamená to, že pole už bolo vytvorené (volanie funkcie n bolo stlačené)
        if (*p_id != NULL){
            //Print všetkých hodnôt z poľa
            printf("VYPIS Z POLIA\n");
            for (int i = 0; i < *p_rec_numb; i++){
                printf("%s: %s\n", names[0], (*p_id)[i]);
                printf("%s: %s\n", names[1], (*p_pos)[i]);
                printf("%s: %s\n", names[2], (*p_type)[i]);
                printf("%s: %s\n", names[3], (*p_value)[i]);
                printf("%s: %s\n", names[4], (*p_time)[i]);
                printf("%s: %s\n", names[5], (*p_date)[i]);
                printf("\n");
            }
        }
        //Ak nie sú vytvorené žiadne polia, vypíše údaje z fólie
        else{
            printf("VYPIS Z SUBORA\n");
            while(!feof(*fr)){
            for (int i = 0; i < amnt_rows; i++){
                printf("%s: ", names[i]);                                        
                fscanf(*fr, "%c", &sign);                                            
                while (!feof(*fr) && (sign != '\n')){                                
                    printf("%c", sign);
                    fscanf(*fr, "%c", &sign);
                }
                printf("%c", sign);                                                 
            }
            fscanf(*fr, "%c", &sign);                                                 
            printf("%c", sign);
            }
            rewind(*fr);
        }
    }
}


void n_func(FILE *fr, char ***p_id, char ***p_pos, char ***p_type, char ***p_value, char ***p_time, char ***p_date, int *p_rec_numb){
    char buffer[50]; //načítaný reťazec sa uloží
    int rec_numb = 0, id_len = 5, pos_len = 14, type_len = 2, time_len = 4, date_len = 8;
    
    if (fr == NULL){
        printf("Neotvoreny subor\n");
    }
    else{
        //Ak boli polia vytvorené, uvoľnite pamäť
        if (*p_id != NULL){
            for (int i = 0; i < *p_rec_numb; i++){
                free((*p_id)[i]);
                (*p_id)[i] = NULL;
                free((*p_pos)[i]);
                (*p_pos)[i] = NULL;
                free((*p_type)[i]);
                (*p_type)[i] = NULL;
                free((*p_value)[i]);
                (*p_value)[i] = NULL;
                free((*p_time)[i]);
                (*p_time)[i] = NULL;
                free((*p_date)[i]);
                (*p_date)[i] = NULL;
            }
            free(*p_id);
            free(*p_pos);
            free(*p_type);
            free(*p_value);
            free(*p_time);
            free(*p_date);
            *p_id = NULL;
            *p_pos = NULL;
            *p_type = NULL;
            *p_value = NULL;
            *p_time = NULL;
            *p_date = NULL;
        }

        //A znovu vytvorte polia
        *p_id = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_id)[rec_numb] = (char*)malloc(sizeof(char)*50);

        *p_pos = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_pos)[rec_numb] = (char*)malloc(sizeof(char)*50);

        *p_type = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_type)[rec_numb] = (char*)malloc(sizeof(char)*50);

        *p_value = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_value)[rec_numb] = (char*)malloc(sizeof(char)*50);

        *p_time = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_time)[rec_numb] = (char*)malloc(sizeof(char)*50);

        *p_date = (char**)malloc(sizeof(char*)*(rec_numb+1));
        (*p_date)[rec_numb] = (char*)malloc(sizeof(char)*50);


        while (!feof(fr)){
            if (rec_numb > 0){
                //na každom kroku, zvyšuje pamäť
                *p_id = (char**)realloc(*p_id, sizeof(char*)*(rec_numb+1));
                (*p_id)[rec_numb] = (char*)malloc(sizeof(char)*50);

                *p_pos = (char**)realloc(*p_pos, sizeof(char*)*(rec_numb+1));
                (*p_pos)[rec_numb] = (char*)malloc(sizeof(char)*50);

                *p_type = (char**)realloc(*p_type, sizeof(char*)*(rec_numb+1));
                (*p_type)[rec_numb] = (char*)malloc(sizeof(char)*50);

                *p_value = (char**)realloc(*p_value, sizeof(char*)*(rec_numb+1));
                (*p_value)[rec_numb] = (char*)malloc(sizeof(char)*50);

                *p_time = (char**)realloc(*p_time, sizeof(char*)*(rec_numb+1));
                (*p_time)[rec_numb] = (char*)malloc(sizeof(char)*50);

                *p_date = (char**)realloc(*p_date, sizeof(char*)*(rec_numb+1));
                (*p_date)[rec_numb] = (char*)malloc(sizeof(char)*50);
            }
        
            //prečíta reťazec a uloží ho do poľa.
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0'; //Odstránenie znaku nového riadku, ak existuje
                    strcpy((*p_id)[rec_numb], buffer);

                }
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0';
                    strcpy((*p_pos)[rec_numb], buffer);

                }
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0';
                    strcpy((*p_type)[rec_numb], buffer);

                }
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0';
                    strcpy((*p_value)[rec_numb], buffer);

                }
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0';
                    strcpy((*p_time)[rec_numb], buffer);

                }
            if (fgets(buffer, sizeof(buffer), fr) != NULL){
                    size_t len = strlen(buffer);
                    if (len > 0 && buffer[len - 1] == '\n')
                        buffer[len - 1] = '\0';
                    strcpy((*p_date)[rec_numb], buffer);

            }
            //prečíta zvyšný prázdny riadok
            fgets(buffer, sizeof(buffer), fr);
            rec_numb++;
        }
        //aktualizuje ukazovateľ v subore
        rewind(fr);
        *p_rec_numb = rec_numb;
    }
}


void c_func(FILE **fr, char ***p_id, char ***p_date, int rec_numb){
    int y_month, compare, data_correct = 1, id_len = 5; 
    int max_sep =-1, month_sep = 0;
    char id_buffer[50], old_id_buffer[50], date_buffer[50], empty[50], year[5], year1[5], month1[3], month[3];

    if (*p_id == NULL){
        printf("Polia nie su vytvorene\n");
    }
    else{
        if ((*fr = fopen("ciachovanie.txt", "r")) != NULL){
            scanf("%d", &y_month);
            for (int i = 0; i < rec_numb; i++){

                int correct_rec = 0; // ak údaje existujú v pamäti -> nastaví sa na 1

                //Skopírujem rok a mesiac z poľa
                strncpy(year, (*p_date)[i], 4); 
                strncpy(month, (*p_date)[i] + 4, 2);
                year[4] = '\0';
                month[2] = '\0';

                
                while (!feof(*fr)){
                    if (fgets(id_buffer, sizeof(id_buffer), *fr) != NULL){
                        fgets(date_buffer, sizeof(date_buffer), *fr);
                        fgets(empty, sizeof(empty), *fr);

                        //overenie id 
                        compare = strncmp((*p_id)[i], id_buffer, 5);
                        //ak sa názvy zhodujú, zistím rozdiel medzi mesiacmi
                        if (compare == 0){
                            correct_rec = 1; //ukazuje, že záznam existuje.
                            strncpy(year1, date_buffer, 4);
                            strncpy(month1, date_buffer + 4, 2);
                            year1[4] = '\0';
                            month1[2] = '\0';

                            //prevádza roky na mesiace + aktuálny mesiac -> porovnanie
                            month_sep = fabs(atoi(year) * 12 + atoi(month)) - (atoi(year1) * 12 + atoi(month1));

                            //ak je rozdiel väčší
                            if (month_sep >= y_month && (month_sep - y_month) > max_sep){
                                max_sep = month_sep - y_month;
                                data_correct = 0; //Označuje, že nie všetky údaje sú správne.
                            }                            
                        }
                    }
                }
                rewind(*fr);

                //Ak aktuálny prvok nie je posledným prvkom v poli a nasledujúci prvok má rovnaké ID 
                if ((i != rec_numb - 1) && strncmp((*p_id)[i], (*p_id)[i+1], 5) == 0){
                    continue;
                }
                else{
                    if (month_sep >= y_month){
                        data_correct = 0;
                        printf("ID. mer. modulu [%s] ma %d mesiacov po ciachovani\n", (*p_id)[i], max_sep);
                    }                      
                    max_sep =-1; 
                    month_sep = 0;
                }          

                //Ak údaje nie sú správne -> výstup 
                if (correct_rec == 0){
                    data_correct = 0;
                    printf("ID. mer. modulu [%s] nie je ciachovany\n", (*p_id)[i], month_sep);

                }    
            }
            
            //Ak sú všetky údaje správne, výstup 
            if (data_correct == 1){
                printf("Data su korektne\n");
            }
            fclose(*fr);
        }
    }
}


void s_func(FILE **fr, char ***p_id,char ***p_pos, char ***p_value, char ***p_type, char ***p_date, char ***p_time, int rec_numb){
    int date_len = 8;
    char **typ_mer = NULL, **typ_value = NULL, **sign_value_1 = NULL, **sign_value_2 = NULL, mer_module[10], mer_vel[5];
    char buffer[50], buffer2[50];
    
    
    if (*p_id == NULL){
        printf("Polia nie su vytvorene\n");
    }
    else{
        //Číta id a typ
        scanf("%s %s", mer_module, mer_vel);
        if ((*fr = fopen("vystup_S.txt", "w")) != NULL){
            //Vytvorí pole na uloženie údajov
            typ_mer = (char **)malloc(sizeof(char*));
            typ_value = (char **)malloc(sizeof(char*));
            sign_value_1 = (char **)malloc(sizeof(char*));
            sign_value_2 = (char **)malloc(sizeof(char*));
            int size = 0;

            for (int i = 0; i < rec_numb; i++){
                int compare, compare2;
                compare = strncmp((*p_id)[i], mer_module, 5);
                compare2 = strncmp((*p_type)[i], mer_vel, 2);

                if ((compare == 0) && (compare2 == 0)) {
                    //Ak sa id a typ zhodujú -> pridať záznam
                    ++size;

                    //Aby sa zabránilo preťaženiu pamäte, kontroluje číslo volania.
                    if (size != 1){
                        typ_mer = (char **)realloc(typ_mer, sizeof(char*)*size);
                        typ_value = (char **)realloc(typ_value, sizeof(char*)*size);
                        sign_value_1 = (char **)realloc(sign_value_1, sizeof(char*)*size);
                        sign_value_2 = (char **)realloc(sign_value_2, sizeof(char*)*size);
                    }

                    typ_mer[size-1] = (char *)malloc(sizeof(char)*20);
                    typ_value[size-1] = (char *)malloc(sizeof(char)*20);
                    sign_value_1[size-1] = (char *)malloc(sizeof(char)*20);
                    sign_value_2[size-1] = (char *)malloc(sizeof(char)*20);

                    

                    //Nastaví dátum
                    strncpy(typ_mer[size-1], (*p_date)[i], 8);
                    strcpy(typ_mer[size-1]+8, (*p_time)[i]);
                    typ_mer[size-1][12] = '\0';

                    //Nastavuje typ
                    strcpy(typ_value[size-1], (*p_value)[i]);
                    typ_value[size-1][9] = '\0';

                    //Nastaví hodnotu 1
                    strncpy(sign_value_1[size-1], (*p_pos)[i], 3);
                    sign_value_1[size-1][3] = '.';
                    strncpy(sign_value_1[size-1]+4, (*p_pos)[i]+3, 4);
                    sign_value_1[size-1][8] = '\0';

                    //Nastaví hodnotu 2
                    strncpy(sign_value_2[size-1], (*p_pos)[i]+7, 3);
                    sign_value_2[size-1][3] = '.';
                    strncpy(sign_value_2[size-1]+4, (*p_pos)[i]+10, 4);
                    sign_value_2[size-1][8] = '\0';
                }
            }

            //bouble sort na triedenie 
            int swapped, numb1, numb2;
            for (int k = 0; k < size - 1; k++) {
                swapped = 0;

                for (int j = 0; j < size - k - 1; j++) {
                    numb1 = atoi(typ_mer[j]);
                    numb2 = atoi(typ_mer[j + 1]);
                    if (numb1 > numb2) {
                        // Swap typ_mer
                        strcpy(buffer2, typ_mer[j]);
                        strcpy(typ_mer[j], typ_mer[j + 1]);
                        strcpy(typ_mer[j + 1], buffer2);

                        //swap typ_value
                        strcpy(buffer2, typ_value[j]);
                        strcpy(typ_value[j], typ_value[j + 1]);
                        strcpy(typ_value[j + 1], buffer2);

                        //swap sign_value_1
                        strcpy(buffer2, sign_value_1[j]);
                        strcpy(sign_value_1[j], sign_value_1[j + 1]);
                        strcpy(sign_value_1[j + 1], buffer2);

                        //sign_value_2
                        strcpy(buffer2, sign_value_2[j]);
                        strcpy(sign_value_2[j], sign_value_2[j + 1]);
                        strcpy(sign_value_2[j + 1], buffer2);
                        swapped = 1;
                    }
                }

                //ak nie je swap -> pole je pripravené(sorted)
                if (swapped == 0) {
                    break;
                }
            }

            // ak size = 0 -> údaje sme nezaznamenali do súboru ciachovanie.txt
            if (size > 0){
                for (int i = 0; i < size; i++){
                    double number = atof(typ_value[i]);
                    fprintf(*fr, "%s\t%.5lf \t%s\t%s\n", typ_mer[i], number, sign_value_1[i], sign_value_2[i]);         
                }
                printf("Pre dany vstup je vytvoreny txt subor\n");
            }
            else
                printf("Pre dany vstup neexistuju zaznamy\n");

            //close file
            fclose(*fr);
            
            //free memory
            for (int i = 0; i < size; i++){
                free(typ_mer[i]);
                typ_mer[i] = NULL;
                free(typ_value[i]);
                typ_value[i] = NULL;
                free(sign_value_1[i]);
                sign_value_1[i] = NULL;
                free(sign_value_2[i]);
                sign_value_2[i] = NULL;
            }
            free(typ_mer);
            free(typ_value);
            free(sign_value_1);
            free(sign_value_2);
            typ_mer = NULL;
            typ_value = NULL;   
            sign_value_1 = NULL;
            sign_value_2 = NULL;
        }
        else{
            printf("Pre dany vstup nie je vytvoreny txt subor.\n");
        }
    }
}


void h_func(char **rec_type, char **value, int rec_numb){
    int counter = 1, res;
    double **value_amnt, numb;
    char **types, buffer[50];

    if (rec_type == NULL)
        printf("Polia nie su vytvorene\n");
    else{
        if (rec_numb != 0){
            //Vytvorí pole na uloženie údajov
            types = (char **)malloc(sizeof(char*)*counter);
            value_amnt = (double **)malloc(sizeof(double*)*counter);
            types[counter-1] = (char *)malloc(sizeof(char)*10);
            value_amnt[counter-1] = (double *)malloc(sizeof(double)*3);

            //prekopírovať hodnotu prvého prvku
            strncpy(types[0], rec_type[0], 2);
            types[0][2] = '\0';

            numb = atof(value[0]);
            value_amnt[counter-1][0] = 1.0; 
            value_amnt[counter-1][1] = numb;
            value_amnt[counter-1][2] = numb;


            for (int j = 1; j < rec_numb; j++){
                res = 0; //premenná označuje, či sa aktuálny typ nachádza v poli alebo ešte nie. 
                for (int i = 0; i < counter; i++){

                    if (strstr(rec_type[j], types[i]) != NULL){
                        res = 1;
                        value_amnt[i][0] += 1;

                        strncpy(buffer, value[j], 6);
                        numb = atof(buffer);
                        //porovnať minimálne a maximálne hodnoty
                        if (numb >= value_amnt[i][1]){
                            value_amnt[i][1] = numb;
                        }
                        else if (numb < value_amnt[i][2]){
                            value_amnt[i][2] = numb;
                        }
                    }
                    
                }
                //Ak sa takýto typ ešte nenachádza v poli
                if (res == 0){
                    counter++;
                    types = (char **)realloc(types, sizeof(char*) * counter);
                    value_amnt = (double **)realloc(value_amnt, sizeof(double *) * counter);

                    types[counter-1] = (char *)malloc(sizeof(char)*5);
                    value_amnt[counter-1] = (double *)malloc(sizeof(double)*3);

                    strncpy(types[counter-1], rec_type[j], 2);
                    types[counter-1][2] = '\0';

                    numb = atof(value[0]);
                    value_amnt[counter-1][0] = 1; 
                    value_amnt[counter-1][1] =  numb;
                    value_amnt[counter-1][2] = numb;
                }
            }
            
            //Print data
            printf("Typ mer.vel.  Pocetnost  Minimum  Maximum\n");
            for (int i = 0; i < counter; i++){
                printf("    %s\t\t  %g\t  %.2lf   %.2lf\t\n", types[i], value_amnt[i][0], value_amnt[i][2], value_amnt[i][1]);
            }

            for (int i = 0; i < counter; i++){
                free(types[i]);
                types[i] = NULL;
                free(value_amnt[i]);
                value_amnt[i] = NULL;
            }
            free(types);
            free(value_amnt);
        }
        else{
            printf("0 zaznamov\n");
        }
    }   
}


void z_func(char ***p_id,char ***p_pos, char ***p_type, char ***p_value, char ***p_time, char ***p_date, int *rec_numb){
    char id_del[10];
    int counter = 0, curr_indx = 0;
    
    if (*p_id == NULL)
        printf("Polia nie su vytvorene.\n"); 
    else{
        //Číta ID, ktoré sa má vymazať 
        scanf("%s", id_del);
        for (int i = 0; i < *rec_numb; i++){

            int compare;
            compare = strncmp(id_del, (*p_id)[i], 5);

            if (compare == 0){
                while (compare == 0){
                    counter++;
                    
                    if (i == *rec_numb - 1){
                        compare = 1;
                    }
                    else {
                        //Ak chcete odstrániť prvok -> posuňte ho na koniec a všetky ostatné prvky o krok doľava.
                        for (int j = i; j < (*rec_numb-1); j++){

                            strcpy((*p_id)[j], (*p_id)[j+1]);                        
                            strcpy((*p_pos)[j], (*p_pos)[j+1]);                    
                            strcpy((*p_type)[j], (*p_type)[j+1]);
                            strcpy((*p_value)[j], (*p_value)[j+1]);
                            strcpy((*p_time)[j], (*p_time)[j+1]);
                            strcpy((*p_date)[j], (*p_date)[j+1]);
                            
                            compare = strncmp(id_del, (*p_id)[i], 5);
                        }
                        
                    }
                    // Odstránenie požadovanej položky
                    free((*p_id)[*rec_numb-1]);
                    free((*p_pos)[*rec_numb-1]);
                    free((*p_type)[*rec_numb-1]);
                    free((*p_value)[*rec_numb-1]);
                    free((*p_time)[*rec_numb-1]);
                    free((*p_date)[*rec_numb-1]);
                    
                    *rec_numb-=1;
                }
            }
        }        
        printf("Vymazalo sa : %d zaznamov !\n", counter);
    }        
}


void k_func(FILE **fr, char ***p_id, char ***p_pos, char ***p_type, char ***p_value, char ***p_time, char ***p_date, int *rec_numb){
    //Ak boli polia vytvorené, uvoľnite pamäť
    if (*p_id != NULL){
        for (int i = 0; i < *rec_numb; i++){
            free((*p_id)[i]);
            (*p_id)[i] = NULL;
            free((*p_pos)[i]);
            (*p_pos)[i] = NULL;
            free((*p_type)[i]);
            (*p_type)[i] = NULL;
            free((*p_value)[i]);
            (*p_value)[i] = NULL;
            free((*p_time)[i]);
            (*p_time)[i] = NULL;
            free((*p_date)[i]);
            (*p_date)[i] = NULL;
        }
        free(*p_id);
        free(*p_pos);
        free(*p_type);
        free(*p_value);
        free(*p_time);
        free(*p_date);
        *p_id = NULL;
        *p_pos = NULL;
        *p_type = NULL;
        *p_value = NULL;
        *p_time = NULL;
        *p_date = NULL;
    }
    *rec_numb = 0;
    if (*fr != NULL)
        fclose(*fr);
        *fr = NULL;
}


int main(){
    FILE *f = NULL, *f_d = NULL, *vystup = NULL;
    int rec_numb = 0; 
    char **p_id = NULL, **p_pos = NULL, **p_type = NULL, **p_value = NULL, **p_time = NULL, **p_date = NULL;
    char sign;

    do
    {
        scanf("%c", &sign);
        switch (sign)
        {
        case 'v':
            v_func(&f, &p_id, &p_pos, &p_type, &p_value, &p_time, &p_date, &rec_numb);
            break;

        case 'n':
            n_func(f, &p_id, &p_pos, &p_type, &p_value, &p_time, &p_date, &rec_numb);
            break;

        case 'c':
            c_func(&f_d, &p_id, &p_date, rec_numb);
            break;

        case 's':
            s_func(&vystup, &p_id,&p_pos, &p_value, &p_type, &p_date, &p_time, rec_numb);
            break;

        case 'h':
            h_func(p_type, p_value, rec_numb);
            break;

        case 'z':
            z_func(&p_id, &p_pos, &p_type, &p_value, &p_time, &p_date, &rec_numb);
            break;
        }
    } while (sign != 'k');
    
    k_func(&f, &p_id, &p_pos, &p_type, &p_value, &p_time, &p_date, &rec_numb);
    return 0;
}