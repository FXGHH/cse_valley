// CSE Valley
// cse_valley.c
//
// This program was written by Yikai Qin (z5378608)
// on 10/2021
//
// Version 1.0.0 (2021-10-04): Assignment Released.
//
// TODO: Description of your program.

#include <stdio.h>
#include <stdlib.h>

#define MAX_NAME_SIZE 50
#define MAX_NUM_SEED_TYPES 26
#define LAND_SIZE 8
#define NO_SEED ' '
#define TRUE 1
#define FALSE 0

struct land {
    int is_watered;
    char seed_name;
};

struct seeds {
    char name;
    int amount;
};

struct farmer {
    int curr_col;
    int curr_row;
    char curr_dir;
};


// HINT: You will be using this function in stage 2!
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE], struct farmer cse_farmer);

// Provided functions use for game setup
// You do not need to use these functions yourself.
struct farmer initialise_farmer(struct farmer cse_farmer);
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]);
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]);
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row);
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE],
                      struct farmer cse_farmer);
void square_watering (int wat_size, struct farmer cse_farmer,
                      struct land farm_land[LAND_SIZE][LAND_SIZE]);
void next_day (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
               struct land farm_land[LAND_SIZE][LAND_SIZE]);
void harvest (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
              struct land farm_land[LAND_SIZE][LAND_SIZE],
              struct farmer cse_farmer);
void trade (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
            char src_name, int src_amt, char dst_name,
            int seed_struct_num, int pre_exist);

int main(void) {

    struct farmer cse_farmer = {};
    cse_farmer = initialise_farmer(cse_farmer);

    struct land farm_land[LAND_SIZE][LAND_SIZE];
    initialise_land(farm_land);

    struct seeds seed_collection[MAX_NUM_SEED_TYPES];
    initialise_seeds(seed_collection);


    printf("Welcome to CSE Valley, farmer!\n");
    printf("Congratulations, you have received 60 seeds.\n");
    printf("How many different seeds do you wish to have? ");

    // TODO: Scan the number of different seeds here!
    // Note: Please remove all TODO's in your submission (including this comment)
    
    int seed_struct_num = 0;
    int seed_type_num, seed_aver_num;
    //struct seeds seed_collection[MAX_NUM_SEED_TYPES] = {0};
    scanf(" %d", &seed_type_num);
    seed_aver_num = 60 / seed_type_num;
    printf("Enter the names of the seeds to be given:\n");
    while (seed_struct_num < seed_type_num) {
        seed_collection[seed_struct_num].amount = seed_aver_num;
        scanf(" %c", &seed_collection[seed_struct_num].name);
        seed_struct_num++;
    }
    // struct seeds seed_collection[MAX_NUM_SEED_TYPES];
    // initialise_seeds(seed_collection);
    printf("Game Started!\n");
    printf("Enter command: ");
    char cmd_loop;
    int day_loop = 2;
    while (scanf(" %c", &cmd_loop) != EOF) {
    // TODO: When you start stage 1.2, you will need to replace the below
    // with a loop that reads and executes commands until EOF.
    // See: https://cs1511.web.cse.unsw.edu.au/short/21T3_a1_explain/
    // for more information!

        if (cmd_loop == 'l') {

            print_land(farm_land, cse_farmer);

        } else if (cmd_loop == 'a') {

            printf(" Seeds at your disposal: \n");
            int j = 0;
            while (j < seed_struct_num) {
                printf(" - %d seed(s) with the name '%c'\n",
                       seed_collection[j].amount, seed_collection[j].name);
                j++;
            }

        } else if (cmd_loop == 's') {

            char seed_name;
            int f = 0;
            int aim_seed = 0;
            scanf(" %c", &seed_name);
            if (seed_name > 'z' || seed_name < 'a') {
                printf("   Seed name has to be a lowercase letter\n");
            } else {
                while (f < seed_struct_num) {
                    if (seed_name == seed_collection[f].name) {
                        aim_seed = f;
                    }
                    f++;
                }
                if (seed_name == seed_collection[aim_seed].name) {
                    printf("  There are %d seeds with name '%c'\n",
                           seed_collection[aim_seed].amount, seed_collection[aim_seed].name);
                } else {
                    printf("  There are no seed with the name '%c'\n", seed_name);
                }
            }

/////////////////////// below is control famer move ////////////////////

        } else if (cmd_loop == '^') {

            if (cse_farmer.curr_dir == '^') {
                if (cse_farmer.curr_row == 0) {
                    cse_farmer.curr_row = 0;
                } else {
                    cse_farmer.curr_row--;
                }
            } else {
                cse_farmer.curr_dir = '^';
            }

        } else if (cmd_loop == 'v') {

            if (cse_farmer.curr_dir == 'v') {
                if (cse_farmer.curr_row == LAND_SIZE - 1) {
                    cse_farmer.curr_row = LAND_SIZE - 1;
                } else {
                    cse_farmer.curr_row++;
                }
            } else {
                cse_farmer.curr_dir = 'v';
            }

        } else if (cmd_loop == '<') {

            if (cse_farmer.curr_dir == '<') {
                if (cse_farmer.curr_col == 0) {
                    cse_farmer.curr_col = 0;
                } else {
                    cse_farmer.curr_col--;
                }
            } else {
                cse_farmer.curr_dir = '<';
            }

        } else if (cmd_loop == '>') {

            if (cse_farmer.curr_dir == '>') {
                if (cse_farmer.curr_col == LAND_SIZE - 1) {
                    cse_farmer.curr_col = LAND_SIZE - 1;
                } else {
                    cse_farmer.curr_col++;
                }
            } else {
                cse_farmer.curr_dir = '>';
            }
////////////////////////// below is watered land ///////////////////////
        } else if (cmd_loop == 'o'){
            char adj_land;
            scanf(" %c", &adj_land);
            if (adj_land == 'w') {
                if (cse_farmer.curr_dir == '>' &&
                    cse_farmer.curr_col != LAND_SIZE - 1) {

                    farm_land[cse_farmer.curr_row][cse_farmer.curr_col + 1].is_watered = 1;

                } else if (cse_farmer.curr_dir == '<' &&
                           cse_farmer.curr_col != 0) {

                    farm_land[cse_farmer.curr_row][cse_farmer.curr_col - 1].is_watered = 1;

                } else if (cse_farmer.curr_dir == 'v' &&
                           cse_farmer.curr_row != LAND_SIZE - 1) {

                    farm_land[cse_farmer.curr_row + 1][cse_farmer.curr_col].is_watered = 1;

                } else if (cse_farmer.curr_dir == '^' &&
                           cse_farmer.curr_row != 0) {

                    farm_land[cse_farmer.curr_row - 1][cse_farmer.curr_col].is_watered = 1;
                }
///////////////////////// below is palnting seeds //////////////////
            } else if (adj_land == 'p') {
                int i = 0;
                char pla_seed;
                scanf(" %c", &pla_seed);
                if (cse_farmer.curr_dir == '>' &&
                    cse_farmer.curr_col != LAND_SIZE - 1) {

                    farm_land[cse_farmer.curr_row][cse_farmer.curr_col + 1].seed_name = pla_seed;

                } else if (cse_farmer.curr_dir == '<' &&
                           cse_farmer.curr_col != 0) {

                    farm_land[cse_farmer.curr_row][cse_farmer.curr_col - 1].seed_name = pla_seed;

                } else if (cse_farmer.curr_dir == 'v' &&
                           cse_farmer.curr_row != LAND_SIZE - 1) {

                    farm_land[cse_farmer.curr_row + 1][cse_farmer.curr_col].seed_name = pla_seed;

                } else if (cse_farmer.curr_dir == '^' &&
                           cse_farmer.curr_row != 0) {

                    farm_land[cse_farmer.curr_row - 1][cse_farmer.curr_col].seed_name = pla_seed;
                }
                while (i < seed_struct_num &&
                       seed_collection[i].name != pla_seed) {
                    i++;
                }
                seed_collection[i].amount--;
            }
///////////////////////// below is scattering seeds ////////////////////////

        } else if (cmd_loop == 'p') {

            char scat_seeds;
            scanf(" %c", &scat_seeds);
            if (scat_seeds > 'z' || scat_seeds < 'a') {
                printf(" Seed name has to be a lowercase letter\n");

            } else {
                int a = 0;
                while (a < seed_struct_num &&
                       seed_collection[a].name != scat_seeds) {
                    a++;
                }
                if (cse_farmer.curr_dir == '>' &&
                    cse_farmer.curr_col != LAND_SIZE - 1) {
                    int k = cse_farmer.curr_col;

                    while (k < LAND_SIZE) {
                        if (seed_collection[a].amount > 0) {
                            farm_land[cse_farmer.curr_row][k].seed_name = scat_seeds;
                            seed_collection[a].amount--;
                            k++;
                            if (seed_collection[a].amount == 0) {
                                k = LAND_SIZE;
                            }
                        } else if (seed_collection[a].amount == 0) {
                            printf("  There is no seed with the name '%c'\n",
                                   scat_seeds);
                            k = LAND_SIZE;
                        }
                    }

                } else if (cse_farmer.curr_dir == 'v' &&
                    cse_farmer.curr_row != LAND_SIZE - 1) {
                    int t = cse_farmer.curr_row;

                    while (t < LAND_SIZE) {
                        if (seed_collection[a].amount > 0) {
                            farm_land[t][cse_farmer.curr_col].seed_name = scat_seeds;
                            seed_collection[a].amount--;
                            t++;
                            if (seed_collection[a].amount == 0) {
                                t = LAND_SIZE;
                            }
                        } else if (seed_collection[a].amount == 0){
                            printf("  There is no seed with the name '%c'\n",
                                   scat_seeds);
                            t = LAND_SIZE;
                        }
                    }
                } else if (seed_collection[a].amount == 0){
                    printf("  There is no seed with the name '%c'\n",
                           scat_seeds);
                }
                else {
                    printf("  You cannot scatter seeds ^ or <\n");
                }

            }
////////////////////////// below can Square Watering ////////////////////
        } else if (cmd_loop == 'w') {

            int wat_size;
            scanf(" %d", &wat_size);
            square_watering (wat_size, cse_farmer, farm_land);

        } else if (cmd_loop == 'n') {

            printf("  Advancing to the next day... Day %d, let's go!\n", day_loop);
            next_day (seed_collection, farm_land);
            cse_farmer = initialise_farmer(cse_farmer);
            day_loop++;

        } else if (cmd_loop == 'h') {

            harvest (seed_collection, farm_land, cse_farmer);

        } else if (cmd_loop == 't') {

            char src_name;
            int src_amt;
            char dst_name;
            scanf(" %c", &src_name);
            scanf(" %d", &src_amt);
            scanf(" %c", &dst_name);
            int pre_exist = 0;
            int t = 0;
            while (t < MAX_NUM_SEED_TYPES) {
                if (dst_name == seed_collection[t].name) {
                    pre_exist = 1;
                 }
                t++;
            }
            if (pre_exist == 0) {
                seed_struct_num++;

                trade (seed_collection, src_name, src_amt,
                       dst_name, seed_struct_num, pre_exist);
            } else {
                trade (seed_collection, src_name, src_amt,
                       dst_name, seed_struct_num, pre_exist);
            }

        } else if (cmd_loop == 'd') {

            char disaster_type;
            scanf(" %c", disaster_type);
            if (disaster_type == 'd') {
                int min_num_plants_to_die;
                scanf(" %d", min_num_plants_to_die);


            } else if (disaster_type == 'w'){


            }

        }


        printf("Enter command: ");

  }
    return 0;
}

////////////////////////////////
//     Provided Functions     //
////////////////////////////////

// Planting on adjacent land
// void adj_plant (struct farmer cse_farmer,
//                 struct seeds seed_collection, struct land farm_land) {
//
//
// }
void drought(struct land farm_land[LAND_SIZE][LAND_SIZE], int min_num_plants_to_die,
             struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {

}

void trade (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
            char src_name, int src_amt, char dst_name,
            int seed_struct_num, int pre_exist) {

    int i = 0;
    int k = 0;
    int ori_seed = 0;
    while (i < MAX_NUM_SEED_TYPES && k == 0) {
        if (src_name == seed_collection[i].name) {
            ori_seed = 1;
            k = 1;
        }
        i++;
    }

    if (('z' < src_name || src_name < 'a') ||
        ('z' < dst_name || dst_name < 'a')) {

        printf("  Seed name has to be a lowercase letter\n");

    } else if (src_amt < 0) {

        printf("  You can't trade negative seeds\n");

    } else if (ori_seed == 0) {

        printf("  You don't have the seeds to be traded\n");

    } else if (seed_collection[i - 1].amount < src_amt) {

        printf("  You don't have enough seeds to be traded\n");

    } else if (pre_exist == 0) {

        int j = 0;
        int l = seed_struct_num;
        seed_collection[i - 1].amount = seed_collection[i - 1].amount - src_amt;
        while (j < seed_struct_num && (l - 2) >= 0) {
            seed_collection[l - 1].name = seed_collection[l - 2].name;
            seed_collection[l - 1].amount = seed_collection[l - 2].amount;
            j++;
            l--;
        }
        seed_collection[0].name = dst_name;
        seed_collection[0].amount = src_amt;

    } else if (pre_exist == 1){
        k = 0;
        int dst = 0;
        int end = 0;
        while (k < MAX_NUM_SEED_TYPES && end == 0) {
            if (dst_name == seed_collection[dst].name) {
                end = 1;
            }
            k++;
            dst++;
        }
        seed_collection[i - 1].amount = seed_collection[i - 1].amount - src_amt;
        seed_collection[dst - 1].amount = seed_collection[dst - 1].amount + src_amt;
    }

}



void harvest (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
              struct land farm_land[LAND_SIZE][LAND_SIZE],
              struct farmer cse_farmer) {

    char p_name;
    char se_name;
    int i = 0;
    if (cse_farmer.curr_dir == '>' &&
        cse_farmer.curr_col != LAND_SIZE - 1) {

        p_name = farm_land[cse_farmer.curr_row][cse_farmer.curr_col + 1].seed_name;
        if (p_name < 'a' && p_name != NO_SEED) {
            se_name = p_name + 32;
            while (i < MAX_NUM_SEED_TYPES) {
                if (seed_collection[i].name == se_name) {
                    seed_collection[i].amount = seed_collection[i].amount + 5;
                }
                i++;
            }
            farm_land[cse_farmer.curr_row][cse_farmer.curr_col + 1].seed_name = NO_SEED;
            printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s)\n",
                   p_name, se_name);
        }


    } else if (cse_farmer.curr_dir == '<' &&
               cse_farmer.curr_col != 0) {
        i = 0;
        p_name = farm_land[cse_farmer.curr_row][cse_farmer.curr_col - 1].seed_name;
        if (p_name < 'a' && p_name != NO_SEED) {
            se_name = p_name + 32;
            while (i < MAX_NUM_SEED_TYPES) {
                if (seed_collection[i].name == se_name) {
                    seed_collection[i].amount = seed_collection[i].amount + 5;
                }
                i++;
            }
            farm_land[cse_farmer.curr_row][cse_farmer.curr_col - 1].seed_name = NO_SEED;
            printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s)\n",
                   p_name, se_name);
        }

    } else if (cse_farmer.curr_dir == 'v' &&
               cse_farmer.curr_row != LAND_SIZE - 1) {
        i = 0;
        p_name = farm_land[cse_farmer.curr_row + 1][cse_farmer.curr_col].seed_name;
        if (p_name < 'a' && p_name != NO_SEED) {
            se_name = p_name + 32;
            while (i < MAX_NUM_SEED_TYPES) {
                if (seed_collection[i].name == se_name) {
                    seed_collection[i].amount = seed_collection[i].amount + 5;
                }
                i++;
            }
            farm_land[cse_farmer.curr_row + 1][cse_farmer.curr_col].seed_name = NO_SEED;
            printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s)\n",
                   p_name, se_name);
        }

    } else if (cse_farmer.curr_dir == '^' &&
               cse_farmer.curr_row != 0) {
        i = 0;
        p_name = farm_land[cse_farmer.curr_row][cse_farmer.curr_col].seed_name;
        if (p_name < 'a' && p_name != NO_SEED) {
            se_name = p_name + 32;
            while (i < MAX_NUM_SEED_TYPES) {
                if (seed_collection[i].name == se_name) {
                    seed_collection[i].amount = seed_collection[i].amount + 5;
                }
                i++;
            }
            farm_land[cse_farmer.curr_row - 1][cse_farmer.curr_col].seed_name = NO_SEED;
            printf("  Plant '%c' was harvested, resulting in 5 '%c' seed(s)\n",
                   p_name, se_name);
        }
    }
}
void next_day (struct seeds seed_collection[MAX_NUM_SEED_TYPES],
               struct land farm_land[LAND_SIZE][LAND_SIZE]) {
    int row = 0;
    while (row < LAND_SIZE) {
        int col = 0;
        while (col < LAND_SIZE) {
            if (farm_land[row][col].is_watered == TRUE &&

                farm_land[row][col].seed_name != NO_SEED) {
                int a = farm_land[row][col].seed_name;
                farm_land[row][col].seed_name = a - 32;
                farm_land[row][col].is_watered = FALSE;

            } else {

                farm_land[row][col].seed_name = NO_SEED;

            }
            col++;
        }
        row++;
    }

}

void square_watering (int wat_size, struct farmer cse_farmer,
                      struct land farm_land[LAND_SIZE][LAND_SIZE]) {

    int h_wat_row = cse_farmer.curr_row - wat_size;
    int e_wat_row = cse_farmer.curr_row + wat_size;

    int h_wat_col = cse_farmer.curr_col - wat_size;
    int e_wat_col = cse_farmer.curr_col + wat_size;

    int row = 0;
    while (row < LAND_SIZE) {
        int col = 0;
        while (col < LAND_SIZE) {
            if (row >= h_wat_row && row <= e_wat_row) {
                if (col >= h_wat_col && col <= e_wat_col) {
                    farm_land[row][col].is_watered = 1;
                }
            }
            col++;
        }
        row++;
    }
}


// Prints the structs land (including locating where the
// farmer is)
// You will need this function in Stage 2.
void print_land(struct land farm_land[LAND_SIZE][LAND_SIZE],
                struct farmer cse_farmer) {
    printf("|---|---|---|---|---|---|---|---|\n");
    int i = 0;
    while (i < LAND_SIZE) {
        print_top_row(farm_land, i);
        // only prints mid and bottom row when the farmer
        // is in that row
        if (i == cse_farmer.curr_row) {
            print_farmer_row(farm_land, cse_farmer);
        }
        printf("|---|---|---|---|---|---|---|---|\n");
        i++;
    }
}

// Initialises struct farmer to its default state upon starting
// in which the farmer will be on the top left of the farm
// facing to the right (as noted by '>')
struct farmer initialise_farmer(struct farmer cse_farmer) {
    cse_farmer.curr_col = 0;
    cse_farmer.curr_row = 0;
    cse_farmer.curr_dir = '>';
    return cse_farmer;
}
// Initialises a 2d array of struct land to its default state
// upon starting, which is that all land is unwatered and
// contains no seed
void initialise_land(struct land farm_land[LAND_SIZE][LAND_SIZE]) {
    int i = 0;
    while (i < LAND_SIZE) {
        int j = 0;
        while (j < LAND_SIZE) {
            farm_land[i][j].is_watered = FALSE;
            farm_land[i][j].seed_name = NO_SEED;
            j++;
        }
        i++;
    }
}

// Initialises struct farmer to its default state upon starting,
// which that all names are initialised as NO_SEED and its
// amount is 0
void initialise_seeds(struct seeds seed_collection[MAX_NUM_SEED_TYPES]) {
    int i = 0;
    while (i < MAX_NUM_SEED_TYPES) {
        seed_collection[i].amount = 0;
        seed_collection[i].name = NO_SEED;
        i++;
    }
}

////////////////////////////////
//      Helper Functions      //
////////////////////////////////

// prints the top row of a particular struct land
void print_top_row(struct land farm_land[LAND_SIZE][LAND_SIZE], int row) {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        printf("%c", farm_land[row][j].seed_name);
        printf(" ");
        if (farm_land[row][j].is_watered == TRUE) {
            printf("W");
        } else {
            printf(" ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}

// prints the 2 additional row when a farmer is in
// a particular row
void print_farmer_row(struct land farm_land[LAND_SIZE][LAND_SIZE],
                      struct farmer cse_farmer)  {
    int j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            if (cse_farmer.curr_dir == '<') {
                printf("<");
            } else {
                printf(" ");
            }

            if (cse_farmer.curr_dir == '^') {
                printf("^");
            } else {
                printf("f");
            }

            if (cse_farmer.curr_dir == '>') {
                printf(">");
            } else {
                printf(" ");
            }
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
    j = 0;
    while (j < LAND_SIZE) {
        printf("|");
        if (j == cse_farmer.curr_col) {
            printf(" ");
            if (cse_farmer.curr_dir == 'v') {
                printf("v");
            } else if (cse_farmer.curr_dir == '^') {
                printf("f");
            } else {
                printf(" ");
            }
            printf(" ");
        } else {
            printf("   ");
        }
        j++;
    }
    printf("|");
    printf("\n");
}
