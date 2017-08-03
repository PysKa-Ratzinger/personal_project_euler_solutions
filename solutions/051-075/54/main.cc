#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <chrono>

#define SCORE_HIGH_VALUE     0
#define SCORE_ONE_PAIR       1
#define SCORE_TWO_PAIRS      2
#define SCORE_THREE_KIND     3
#define SCORE_STRAIGHT       4
#define SCORE_FLUSH          5
#define SCORE_FULL_HOUSE     6
#define SCORE_FOUR_KIND      7
#define SCORE_STRAIGHT_FLUSH 8
#define SCORE_ROYAL_FLUSH    9

#define FILE_NAME "p054_poker.txt"
#define BUFFER_SZ 512

struct card{
    unsigned char value;    // 0 - 12
    unsigned char suit;     // 0 - 3
};

struct hand{
    struct card cards[5];
};

struct game{
    struct hand players[2];
};

struct score{
    unsigned int value;
    struct score* next;
};

unsigned get_index(char* arr, char target, unsigned arrsize){
    for(unsigned i=0; i<arrsize; i++){
        if(target == arr[i]){
            return i;
        }
    }
    return arrsize;
}

void read_card(char* pointer, struct card* card){
    unsigned char value = *pointer;
    if(value >= '2' && value <= '9'){
        value -= '2';
    }else{
        char tmparr[]{'T', 'J', 'Q', 'K', 'A'};
        value = get_index(tmparr, value, sizeof(tmparr));
        if(value == sizeof(tmparr)){
            fprintf(stderr, "Something went wrong.\n");
            fprintf(stderr, "%s\n", pointer);
            exit(EXIT_FAILURE);
        }
        value += 8;
    }

    pointer++;
    unsigned char suit = *pointer;
    char tmparr[]{'H', 'C', 'S', 'D'};
    suit = get_index(tmparr, suit, sizeof(tmparr));
    if(suit == sizeof(tmparr)){
            fprintf(stderr, "Something went wrong.\n");
            fprintf(stderr, "%s\n", pointer);
            exit(EXIT_FAILURE);
    }

    card->value = value;
    card->suit = suit;
}

void read_cards(char* buffer, struct game* game){
    char* p = buffer;
    for(int i=0; i<10; i++){
        read_card(p, &game->players[i/5].cards[i%5]);
        p += 3;
    }
    for(int i=0; i<2; i++){
        struct hand* curr = &game->players[i];
        for(int j=0; j<4; j++){
            for(int k=j+1; k<5; k++){
                if(curr->cards[j].value > curr->cards[k].value){
                    struct card temp;
                    memcpy(&temp, &curr->cards[j], sizeof(struct card));
                    memcpy(&curr->cards[j], &curr->cards[k], sizeof(struct card));
                    memcpy(&curr->cards[k], &temp, sizeof(struct card));
                }
            }
        }
    }
}

struct score* createScore(unsigned int value, struct score* nextValue){
    struct score* res = (struct score*) malloc(sizeof(score));
    res->value = value;
    res->next = nextValue;
    return res;
}

void deleteScore(struct score* score){
    if(score->next) free(score->next);
    free(score);
}

struct score* scoreHighCard(struct hand* hand){
    unsigned char values[5];
    for(int i=0; i<5; i++){
        values[i] = hand->cards[i].value;
    }
    for(int i=0; i<4; i++){
        for(int j=i+1; j<5; j++){
            if(values[i] > values[j]){
                unsigned char temp = values[i];
                values[i] = values[j];
                values[j] = temp;
            }
        }
    }
    struct score* res = NULL;
    for(int i=0; i<5; i++){
        res = createScore(values[i], res);
    }
    return createScore(SCORE_HIGH_VALUE, res);
}

struct score* scoreOnePair(struct hand* hand){
    int values[5]{0};
    int reps[5]{0};
    int size = 0;
    for(int i=0; i<5; i++){
        int tmpVal = hand->cards[i].value;
        int j=0;
        for(; j<size; j++){
            if(tmpVal == values[j]){
                reps[j]++;
                break;
            }
        }
        if(j == size){
            values[size] = tmpVal;
            reps[size++] = 1;
        }
    }
    if(size != 4) return NULL;
    for(int i=0; i<5; i++){
        if(reps[i] == 2){
            return createScore(SCORE_ONE_PAIR, createScore(values[i],
                        scoreHighCard(hand)));
        }
    }
    return NULL;
}

struct score* scoreTwoPairs(struct hand* hand){
    int values[5]{0};
    int reps[5]{0};
    int size = 0;
    for(int i=0; i<5; i++){
        int tmpVal = hand->cards[i].value;
        int j=0;
        for(; j<size; j++){
            if(tmpVal == values[j]){
                reps[j]++;
            }
        }
        if(j == size){
            values[size] = tmpVal;
            reps[size++] = 1;
        }
    }
    int res = 0;
    for(int i=0; i<size; i++){
        if(reps[i] == 2){
            res++;
        }
    }
    if(res != 2) return NULL;
    for(int i=0; i<2; i++){
        if(reps[i] == 1){
            int temp = values[i];
            values[i] = values[2];
            values[2] = temp;
            reps[i] = 2;
            reps[2] = 1;
            break;
        }
    }
    if(values[0] < values[1]){
        int temp = values[0];
        values[0] = values[1];
        values[1] = temp;
    }
    return createScore(SCORE_TWO_PAIRS, createScore(values[0],
            createScore(values[1], createScore(values[2], NULL))));
}

struct score* scoreThreeOfAKind(struct hand* hand){
    int res = 0;
    int rep = 0;
    for(int i=0; i<5; i++){
        if(rep == 0){
            rep++;
        }else{
            if(hand->cards[i].value == hand->cards[i-1].value){
                rep++;
            }else{
                rep = 1;
            }
            if(rep > res){
                res = rep;
            }
        }
    }
    if(res != 3){
        return NULL;
    }else{
        return createScore(SCORE_THREE_KIND, scoreHighCard(hand));
    }
}

struct score* scoreStraight(struct hand* hand){
    for(int i=0; i<4; i++)
        if(hand->cards[i].value != hand->cards[i+1].value - 1)
            return NULL;
    return createScore(SCORE_STRAIGHT, scoreHighCard(hand));
}

struct score* scoreFlush(struct hand* hand){
    unsigned char suit = hand->cards[0].suit;
    for(int i=1; i<5; i++){
        if(hand->cards[i].suit != suit)
            return NULL;
    }
    return createScore(SCORE_FLUSH, scoreHighCard(hand));
}

struct score* scoreFullHouse(struct hand* hand){
    if(hand->cards[0].value == hand->cards[1].value &&
            hand->cards[3].value == hand->cards[4].value &&
            (hand->cards[1].value == hand->cards[2].value ||
            hand-> cards[2].value == hand->cards[3].value)){
        return createScore(SCORE_FULL_HOUSE, createScore(hand->cards[2].value,
                createScore(hand->cards[1].value == hand->cards[2].value ?
                    hand->cards[3].value : hand->cards[1].value, NULL)));
    }else{
        return NULL;
    }
}

struct score* scoreFourOfAKind(struct hand* hand){
    int same = 0;
    for(int i=0; i<5; i++){
        if(i == 1) continue;
        if(hand->cards[i].value == hand->cards[1].value)
            same++;
    }
    if(same != 4) return NULL;
    unsigned char tempValue = 0;
    if(hand->cards[0].value != hand->cards[1].value)
        tempValue = hand->cards[0].value;
    else tempValue = hand->cards[4].value;
    return createScore(SCORE_FOUR_KIND, createScore(hand->cards[1].value,
            createScore(tempValue, NULL)));
}

struct score* scoreStraightFlush(struct hand* hand){
    struct score* flush = scoreFlush(hand);
    if(flush == NULL) return NULL;
    deleteScore(flush);
    struct score* straight = scoreStraight(hand);
    if(straight == NULL) return NULL;
    deleteScore(straight);
    return createScore(SCORE_STRAIGHT_FLUSH, scoreHighCard(hand));
}

struct score* scoreRoyalFlush(struct hand* hand){
    struct score* flush = scoreFlush(hand);
    if(flush == NULL) return NULL;
    deleteScore(flush);
    for(int i=0; i<5; i++)
        if(hand->cards[i].value != 8+i) return NULL;
    return createScore(SCORE_ROYAL_FLUSH, NULL);
}

void insertTail(struct score* score, struct score* tail){
    struct score* pointer = score;
    while(pointer->next){
        pointer = pointer->next;
    }
    pointer->next = tail;
}

struct score* get_score(struct hand* hand){
    struct score* scores[10];
    scores[0] = scoreRoyalFlush(hand);
    scores[1] = scoreStraightFlush(hand);
    scores[2] = scoreFourOfAKind(hand);
    scores[3] = scoreFullHouse(hand);
    scores[4] = scoreFlush(hand);
    scores[5] = scoreStraight(hand);
    scores[6] = scoreThreeOfAKind(hand);
    scores[7] = scoreTwoPairs(hand);
    scores[8] = scoreOnePair(hand);
    scores[9] = scoreHighCard(hand);

    struct score* res = NULL;
    for(int i=0; i<10; i++){
        if(scores[i] != NULL){
            if(res == NULL){
                res = scores[i];
            }else{
                insertTail(res, scores[i]);
            }
        }
    }
    return res;
}

int game_result(struct game* game){
    struct score* scores[2];
    for(int i=0; i<2; i++){
        scores[i] = get_score(&game->players[i]);
    }
    int res = 0;
    struct score* it[2];
    it[0] = scores[0];
    it[1] = scores[1];
    while(it[0] && it[1]){
        if(it[0]->value > it[1]->value){
            res = 1;
            goto end;
        }else if(it[0]->value < it[1]->value){
            res = 2;
            goto end;
        }
        it[0] = it[0]->next;
        it[1] = it[1]->next;
    }
    if(it[0] && !it[1]){
        res = 1;
    }else if(!it[0] && it[1]){
        res = 2;
    }else{
        res = 0;
    }
    end:
    deleteScore(scores[0]);
    deleteScore(scores[1]);
    return res;
}

int main(){
    unsigned long res = 0;
    char buffer[BUFFER_SZ];
    // printf("Input file name: ");
    // fgets(buffer, BUFFER_SZ, stdin);
    // buffer[strlen(buffer)-1] = '\0';

    FILE* input_file;
    if((input_file = fopen(FILE_NAME, "r")) == NULL){
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    std::chrono::high_resolution_clock::time_point t1 =
        std::chrono::high_resolution_clock::now();

    while((fgets(buffer, BUFFER_SZ, input_file)) != NULL){
        struct game game;
        read_cards(buffer, &game);
        int tmp = 0;
        if((tmp = game_result(&game)) == 1){
            res++;
        }
    }

    std::chrono::high_resolution_clock::time_point t2 =
        std::chrono::high_resolution_clock::now();
    unsigned long duration =
        std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    printf("If you can trust me, the number you are "
            "looking for is %lu\n", res);
    printf("Execution time: %lums\n", duration/1000);
    return 0;
}
