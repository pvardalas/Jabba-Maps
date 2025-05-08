/*
    Panagiotis Vardalas
*/

// Libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Stores data for the next possible stops of every stop
struct nextstops {
    // The name of the next possible stop
    char ** names;
    // The distanse from the next possible stop
    int * dist;
    // The counter of the next possible stops found in the file
    int count;
};

// Stores data for the passed stops
struct stopspassed {
    char ** names;
    int count;
};

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }
    FILE *f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "File doesn't exist.\n");
        return 1;
    }

    int count = 0, dist = 0, flag1 = -1, flag2 = 0, flag3 = 0, flag4 = 0;

    //  Stores the names of all the stops
    char ** stops = malloc(2 * sizeof(char *));
    for (int i = 0; i < 2; i++) stops[i] = malloc(100 * sizeof(char));

    // Define the nextstops struct with 2 empty elements
    struct nextstops *nextstop = malloc(2 * sizeof(struct nextstops));
    for (int i = 0; i < 1; i++) {
        nextstop[i].names = malloc(sizeof(char *));
        nextstop[i].names[0] = malloc(100 * sizeof(char));
        nextstop[i].dist = malloc(sizeof(int));
        nextstop[i].count = 0;
    }

    struct stopspassed passed;
    passed.names = malloc(sizeof(char *));
    passed.names[0] = malloc(100 * sizeof(char));
    passed.count = 0;

    
    char *city1 = malloc(100 * sizeof(char));
    char *city2 = malloc(100 * sizeof(char));
    while (fscanf(f, "%99[^-]-%99[^:]: %d\n", city1, city2, &dist) == 3) {
        flag1 = 0;
        flag2 = 0;
        if (count >= 2) {
            for (int i = 0; i < count; i++) {
                if (flag1 && flag2) break;
                if (strcmp(city1, stops[i]) == 0) flag1 = 1;
                if (strcmp(city2, stops[i]) == 0) flag2 = 1;
            }
            if (!flag1) {
                count++;
                stops = realloc(stops, count * sizeof(char *));
                stops[count-1] = malloc(100 * sizeof(char));
                strcpy(stops[count-1], city1);
                nextstop = realloc(nextstop, count * sizeof(struct nextstops));
                nextstop[count-1].names = malloc(sizeof(char *));
                nextstop[count-1].names[0] = malloc(100 * sizeof(char));
                nextstop[count-1].count = 0;
                nextstop[count-1].dist = malloc(sizeof(int));
            }
            flag3 = 0;
            flag4 = 0;
            for (int i = 0; i < passed.count; i++) {
                if (strcmp(city2, passed.names[i]) == 0) flag3 = 1;
            }
            if (!flag3) {

                // Adding new stop and for that stop adding nextstop data
                for (int i = 0; i < count; i++) {
                    if (strcmp(city1, stops[i]) == 0) {
                            nextstop[i].count++;
                            nextstop[i].names = realloc(nextstop[i].names, nextstop[i].count * sizeof(char *));
                            nextstop[i].names[nextstop[i].count-1] = malloc(100 * sizeof(char));
                            nextstop[i].dist = realloc(nextstop[i].dist, nextstop[i].count * sizeof(int));
                            strcpy(nextstop[i].names[nextstop[i].count-1], city2);
                            nextstop[i].dist[nextstop[i].count-1] = dist;
                            break;     
                    }
                }

            }
            if (!flag2) {
                count++;
                stops = realloc(stops, count * sizeof(char *));
                stops[count-1] = malloc(100 * sizeof(char));
                strcpy(stops[count-1], city2);
                nextstop = realloc(nextstop, count * sizeof(struct nextstops));
                nextstop[count-1].names = malloc(sizeof(char *));
                nextstop[count-1].names[0] = malloc(100 * sizeof(char));
                nextstop[count-1].count = 0;
                nextstop[count-1].dist = malloc(sizeof(int));
            }
            for (int i = 0; i < passed.count; i++) {
                if (strcmp(city1, passed.names[i]) == 0) flag4 = 1;
            }

            if (!flag4) {
                for (int i = 0; i < count; i++) {
                    if (strcmp(city2, stops[i]) == 0) {
                            nextstop[i].count++;
                            nextstop[i].names = realloc(nextstop[i].names, nextstop[i].count * sizeof(char *));
                            nextstop[i].names[nextstop[i].count-1] = malloc(100 * sizeof(char));
                            nextstop[i].dist = realloc(nextstop[i].dist, nextstop[i].count * sizeof(int));
                            strcpy(nextstop[i].names[nextstop[i].count-1], city1);
                            nextstop[i].dist[nextstop[i].count-1] = dist; 
                            break;        
                    }
                }
            }
        }
        else {
            strcpy(stops[0], city1);
            strcpy(stops[1], city2);
            strcpy(nextstop[0].names[0], city2);
            nextstop[0].dist[nextstop[0].count] = dist;
            nextstop[0].count++;
            count = 2;
            strcpy(passed.names[passed.count], city1);
            passed.count++;
        } 
    }

    fclose(f);
    if (flag1 == -1) {
        fprintf(stderr, "The file is empty!\n");
        exit(EXIT_FAILURE);
    }
    passed.names = realloc(passed.names, count * sizeof(char *));
    for (int i = 1; i < count; i++) passed.names[i] = malloc(100 * sizeof(char));
    int min=0, flagm = 0, cal;
    char ** minroute = malloc(count * sizeof(char *));
    for (int i = 0; i < count; i++) minroute[i] = malloc(100 * sizeof(char));
    // for (int i = 0; i < )
    // while (passed.count < count) {
    int pos = 0;
    // Loops every possible first nextstop

    int first = 1;
    int pos2 = 0;
    pos = 0;
    cal = 0;
    for (int l = 0; l < nextstop[0].count; l++) {
        pos = 0;
        // printf("Did pos=0\n");
        for (int j = count-1; j > 0; j--) {
            passed.names[j][0] = '\0';
        }
        passed.count=1;
        for (int i = 0; i < nextstop[pos].count; i++) {
            if (pos == 0) i = l;
            flagm = 0;
            // Checking if the next possible stop has already been visited
            for (int m = 0; m < passed.count; m++) {
                if (strcmp(nextstop[pos].names[i], passed.names[m]) == 0) {
                    flagm = 1;
                    break;      
                }
            }
            if (!flagm) {
                passed.names[passed.count][0] = '\0';
                strcpy(passed.names[passed.count], nextstop[pos].names[i]);
                pos2 = passed.count;
                passed.count++;
                for (int j = 0; j < count; j++) {
                    if (strcmp(stops[j], nextstop[pos].names[i]) == 0) {
                        pos = j;
                        if (passed.count < count) i = -1;
                        break;
                    }
                }
                if (passed.count == count) {
                    for (int j = 0; j < count-1; j++) {
                        for (int k = 0; k < count; k++) {
                            if (strcmp(passed.names[j], stops[k]) == 0) {
                                for (int m = 0; m < nextstop[k].count; m++) {
                                    if (strcmp(passed.names[j+1], nextstop[k].names[m]) == 0) {
                                        cal += nextstop[k].dist[m];
                                        break;
                                    }
                                }
                                break;
                            }
                        }
                    }

                    if (cal < min || first) {
                        for (int j = 0; j < count; j++) strcpy(minroute[j], passed.names[j]); //minroute[j] = passed.names[j];
                        min = cal;
                    }
                    first = 0;
                    cal = 0;
                    int n=1;
                    while (n) {
                        for (int j = 0; j < count; j++) {
                            if (strcmp(passed.names[pos2-1], stops[j]) == 0) {
                                for (int k = 0; k < nextstop[j].count; k++) {
                                    if (strcmp(nextstop[j].names[k], passed.names[pos2]) == 0) {
                                        if (k < nextstop[j].count-1) {
                                            int flag_ = 0;
                                            for (int p = k+1; p < nextstop[j].count; p++) {
                                                flag_ = 0;
                                                for (int o = 0; o < pos2; o++) {
                                                    if (strcmp(passed.names[o], nextstop[j].names[p]) == 0) {
                                                        flag_ = 1;
                                                        break;
                                                    }
                                                }
                                                if (flag_ == 0) {
                                                    pos = j;
                                                    i = p-1;
                                                    j=p=k=count+1;
                                                    n=0;                                           
                                                    passed.count = pos2;
                                                    break;
                                                }
                                            }
                                            if (flag_ == 1) {
                                                if (pos2 == 2) {
                                                    n=0;
                                                    exit(1);
                                                }
                                                else {
                                                    pos2--;
                                                    passed.count = pos2+1;
                                                }
                                                j=k=count+1;
                                                break;
                                            }
                                        }
                                        else if(k >= nextstop[j].count-1) {
                                            if (pos2 <= 2) {
                                                i = nextstop[pos].count;
                                                n = 0;
                                            }
                                            else {
                                                passed.count = pos2 +1;
                                                pos2--;
                                            }
                                            j=k=count+1;
                                            break;
                                        }
                                    }
                                    if (k == count+1) break;
                                }
                            }
                            if (j == count+1) break;
                        }
                    }
                }
            }
        }
    }
    printf("We will visit the cities in the following order:\n");
    for (int j = 0; j < count-1; j++) {
        for (int k = 0; k < count; k++) {
            if (strcmp(passed.names[j], stops[k]) == 0) {
                for (int m = 0; m < nextstop[k].count; m++) {
                    if (strcmp(passed.names[j+1], nextstop[k].names[m]) == 0) {
                        printf("%s -(%d)-> ", minroute[j], nextstop[k].dist[m]);
                        break;
                    }
                }
                break;
            }
        }
    }
    printf("%s\n",minroute[count-1]);
    printf("Total cost: %d\n", min);
    for (int i = 0; i < count; i++) {
        free(nextstop[i].names);
        free(nextstop[i].dist);
        free(passed.names[i]);
    }
    free(nextstop);
    free(passed.names);

    return 0;
}
