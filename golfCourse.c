#include <stdio.h>
#include <stdlib.h>


struct HoleScore {
    int holeNumber;
    int score;
    int par;
};

struct Player {
    int playerId;
    char name[50];
    int totalscore;
    int hasFinished; 
    struct HoleScore* hole[5];
};
struct Player players[4] = {
    {1, "Player A", 0, 0, {NULL, NULL, NULL, NULL, NULL}},
    {2, "Player B", 0, 0, {NULL, NULL, NULL, NULL, NULL}},
    {3, "Player C", 0, 0, {NULL, NULL, NULL, NULL, NULL}},
    {4, "Player D", 0, 0, {NULL, NULL, NULL, NULL, NULL}}
};
int finishedPlayers = 0; 
int holeNumber = 0;

void printTable(struct Player* players, int holeNumber) {
    printf("+-----------");
    for (int i = 1; i <= 5; i++) {
        printf("+-----------");
    }
    printf("+-----------+\n");

    printf("|           ");
    for (int i = 1; i <= 5; i++) {
        printf("| Hole %d    ", i);
    }
    printf("| Hole Avg|\n");

    printf("+-----------");
    for (int i = 1; i <= 5; i++) {
        printf("+-----------");
    }
    printf("+-----------+\n");

    for (int i = 0; i < 4; i++) {
        printf("| %s  ", players[i].name);

        for (int j = 0; j < 5; j++) {
            if(players[i].hole[j])
                printf("| %-9d ", players[i].hole[j]->score);
            else
                printf("| %-9d ", 0);
        }

        float playerAvg = 0.0;
        for (int j = 0; j < 5; j++) {
            if(players[i].hole[j])
                playerAvg += players[i].hole[j]->score;
        }
        playerAvg /= 5;

        printf("| %-9.2f |\n", playerAvg);

        if (i < 4) {
            printf("+-----------");
            for (int j = 1; j <= 5; j++) {
                printf("+-----------");
            }
            printf("+-----------+\n");
        }
    }
    printf("+-----------");
    for (int i = 1; i <= 5; i++) {
        printf("+-----------");
    }
    printf("+-----------+\n");

    printf("| Total     ");
    for (int j = 0; j < 5; j++) {
        int total = 0;
        for (int i = 0; i < 4; i++) {
            if(players[i].hole[j])
                total += players[i].hole[j]->score;
        }
        printf("| %-9d ", total);
    }
    printf("|           |\n");

    printf("| Average   ");
    for (int j = 0; j < 5; j++) {
        int total = 0;
        for (int i = 0; i < 4; i++) {
            if(players[i].hole[j])
                total += players[i].hole[j]->score;
        }
        float average = (float)total / 4;
        printf("| %-9.2f ", average);
    }

    float overallAvg = 0.0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 5; j++) {
            if(players[i].hole[j])
                overallAvg += players[i].hole[j]->score;
        }
    }
    overallAvg /= (4 * 5);

    printf("| %-9.2f |\n", overallAvg);

    printf("+-----------");
    for (int i = 1; i <= 5; i++) {
        printf("+-----------");
    }
    printf("+-----------+\n");

    printf("| Highest   ");
    for (int j = 0; j < holeNumber; j++) {
        int highest;
        if(players[0].hole[j])
            highest = players[0].hole[j]->score;
            
        for (int i = 0; i < 4; i++) {
            if (players[i].hole[j]->score > highest) {
                highest = players[i].hole[j]->score;
            }
        }
        printf("| %-9d ", highest);
    }
    printf("|           |\n");

    printf("| Lowest    ");
    for (int j = 0; j < holeNumber; j++) {
        int lowest = players[0].hole[j]->score;
        for (int i = 0; i < 4; i++) {
            if (players[i].hole[j]->score < lowest) {
                lowest = players[i].hole[j]->score;
            }
        }
        printf("| %-9d ", lowest);
    }
    printf("|           |\n");

    printf("+-----------");
    for (int i = 1; i <= 5; i++) {
        printf("+-----------");
    }
    printf("+-----------+\n");
}


struct HoleScore* createHole(int holenumber) {
    struct HoleScore* new_node = (struct HoleScore*) malloc(sizeof(struct HoleScore*));
    new_node->holeNumber = holeNumber;
    new_node->score = 0;
    new_node->par = 10;

    return new_node;
}


int handleTurn(struct Player* player, int holeNumber) {
    if (player->hasFinished) {
        return 2;
    }
    printf("It's %s's turn.\n", player->name);
    int input;
    printf("Enter 1 to continue, 2 to end your turn: ");
    scanf("%d", &input);

    if (input == 1) {
        player->hole[holeNumber]->score++;
        printf("Continuing with %s's turn...\n", player->name);
    } else if (input == 2) {
        printf("Ending %s's turn...\n", player->name);
        finishedPlayers++;
        player->hole[holeNumber]->score++;
        player->hasFinished = 1;
    } else {
        printf("Invalid input. Please enter 1 to continue or 2 to end your turn.\n");
    }

    return input;
}

void displayScores(struct Player* player, int holeNumber){
    printf("%s's score: %d\n", player->name, player->hole[holeNumber]->score);
}

int main() {
    system("clear");
    while (holeNumber < 5) {
        for (int i = 0; i < 4; i++) {
            players[i].hole[holeNumber] = createHole(holeNumber);
        }

        printf("Scores after hole %d:\n", holeNumber + 1);
        printTable(players, holeNumber);

        while (finishedPlayers < 4) {
            for (int i = 0; i < 4; ++i) {
                int result = handleTurn(&players[i], holeNumber);
                if (result == 2) {
                    continue;
                }
            }
        }

        for (int i = 0; i < 4; ++i) {
            players[i].hasFinished = 0;
        }

        printf("All players have finished their turns.\nHeading to hole %d\n", (holeNumber + 1));
        finishedPlayers = 0;

        for (int i = 0; i <= 3; i++) {
            displayScores(&players[i], holeNumber);
            players[i].totalscore += players[i].hole[holeNumber]->score;
        }
        holeNumber++;
        system("clear");
    }
    printf("Final Scores:\n");
    printTable(players, holeNumber);
    return 0;
}
