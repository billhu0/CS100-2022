#include <stdio.h>

int n, T;
/*  1 2 3 4 5 6 7 8  9 10 11 12 13 14
    3 4 5 6 7 8 9 10 J Q  K  A  2  Joker */
int cards[20];
int ans;


/* Find one valid combination and play */
void check(int d){
    /* Cannot be the best solution */
    if(d >= ans)
        return;
    /* Find sequence of solo */
    int seq_len = 0;
    /* Twos and jokers are not allowed */
    for(int i = 1; i <= 12; ++i){
        /* Sequence breaks, reset to 0 */
        if(cards[i] == 0){
            seq_len = 0;
        }
        else{
            ++seq_len;
            if(seq_len >= 5){
                /* Play cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    --cards[j];
                check(d + 1);
                /* Reset cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    ++cards[j];
            }
        }
    }
    /* Find sequence of pair */
    seq_len = 0;
    /* Twos and jokers are not allowed */
    for(int i = 1; i <= 12; ++i){
        /* Sequence breaks, reset to 0 */
        if(cards[i] <= 1){
            seq_len = 0;
        }
        else{
            ++seq_len;
            if(seq_len >= 3){
                /* Play cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    cards[j] -= 2;
                check(d + 1);
                /* Reset cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    cards[j] += 2;
            }
        }
    }
    /* Find sequence of trio */
    seq_len = 0;
    for(int i = 1; i <= 12; ++i){
        /* Sequence breaks, reset to 0 */
        if(cards[i] <= 2){
            seq_len = 0;
        }
        else{
            ++seq_len;
            if(seq_len >= 2){
                /* Play cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    cards[j] -= 3;
                check(d + 1);
                /* Reset cards */
                for(int j = i; j >= i - seq_len + 1; --j)
                    cards[j] += 3;
            }
        }
    }
    /* Find trio and four */
    for(int i = 1; i <= 13; ++i){
        if(cards[i] == 3){
            /* Play a trio */
            cards[i] -= 3;
            /* Attach a solo */
            for(int j = 1; j <= 14; ++j){
                /* This card is not available */
                if(cards[j] == 0 || j == i)
                    continue;
                /* Play the solo */
                --cards[j];
                check(d + 1);
                /* Reset the solo */
                ++cards[j];
            }
            /* Attach a pair */
            for(int j = 1; j <= 13; ++j){
                /* This card is not available */
                if(cards[j] <= 1 || j == i)
                    continue;
                /* Play the pair */
                cards[j] -= 2;
                check(d + 1);
                /* Reset the pair */
                cards[j] += 2;
            }
            /* Reset the trio */
            cards[i] += 3;
        }
        else if(cards[i] == 4){
            /* Either a trio or a four is possible */
            /* Play a trio */
            cards[i] -= 3;
            /* Attach a solo */
            for(int j = 1; j <= 14; ++j){
                /* This card is not available */
                if(cards[j] == 0 || j == i)
                    continue;
                /* Play the solo */
                --cards[j];
                check(d + 1);
                /* Reset the solo */
                ++cards[j];
            }
            /* Attach a pair */
            for(int j = 1; j <= 13; ++j){
                if(cards[j] <= 1 || j == i)
                    continue;
                /* Play the pair */
                cards[j] -= 2;
                check(d + 1);
                /* Reset the pair */
                cards[j] += 2;
            }
            /* Reset the trio*/
            cards[i] += 3;

            /* Play a four */
            cards[i] -= 4;
            /* Attach 2 solos */
            for(int j = 1; j <= 14; ++j){
                /* This card is not available */
                if(cards[j] == 0 || j == i)
                    continue;
                /* Play the first solo */
                --cards[j];
                for(int k = j + 1; k <= 14; ++k){
                    if(cards[k] <= 0 || k == j)
                        continue;
                    /* Play the second solo */
                    --cards[k];
                    check(d + 1);
                    /* Reset the second solo */
                    ++cards[k];
                }
                /* Reset the first solo */
                ++cards[j];
            }
            /* Attach 2 pairs */
            for(int j = 1; j <= 13; ++j){
                /* This card is not available */
                if(cards[j] <= 1 || j == i)
                    continue;
                /* Play the first pair */
                cards[j] -= 2;
                for(int k = 1; k <= 13; ++k){
                    if(cards[k] <= 1 || k == j)
                        continue;
                    /* Play the second pair */
                    cards[k] -= 2;
                    check(d + 1);
                    /* Reset the second pair */
                    cards[k] += 2;
                }
                /* Reset the first pair */
                cards[j] += 2;
            }
            /* Reset the four */
            cards[i] += 4;
        }
    }
    for(int i = 1; i <= 14; ++i){
        if(cards[i] != 0)
            ++d;
    }
    ans = d < ans ? d : ans;
}


int main(){
    scanf("%d%d", &T, &n);
    while(T--){
        ans = 10000;
        int x;
        for(int i = 0; i < 20; i++)
            cards[i] = 0;
        for(int i = 0; i < n; i++){
            scanf("%d", &x);
            if(x == 14)
                cards[14]++;
            else if(x == 1)
                cards[12]++;
            else if(x == 2)
                cards[13]++;
            else if(x == 11)
                cards[9]++;
            else if(x == 12)
                cards[10]++;
            else if(x == 13)
                cards[11]++;
            else
                cards[x-2]++;
        }
        check(0);
        printf("%d\n", ans);
    }
    return 0;
}