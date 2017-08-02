# include<stdio.h>
# include<stdlib.h>
# include<time.h>
# include<unistd.h>
# define LEN 6

typedef struct GameDoubleColor//双色球球号信息结构体
{
    int red[LEN];//六红
    int blue;//一蓝
}GAMEDC;

GAMEDC * produce_number_rand(void);//开奖随机号码
GAMEDC * produce_number_player(void);//机选号码投注
GAMEDC * input_number_player(void);//自选号码投注
int print_choose(void);//机选、自选界面
void print_result(const int,const int);//开奖显示界面
void compare(const GAMEDC * const, const GAMEDC * const);//开奖号与投注号比较
void print_number(GAMEDC * NUM);//号码显示

int main(void)
{
    int choose;
    GAMEDC * Player = NULL;
    GAMEDC * Rand = NULL;

    choose = print_choose();
    if(choose == 1)
        Player = produce_number_player();
    else
        Player = input_number_player();

    Rand = produce_number_rand();

    compare(Player,Rand);

    return 0;
}

int print_choose(void)
{
    int choose;

    printf("Welcome to Games!\n");
    printf("(1)produce_number\t(2)input_number\n");
    printf("Please input your choose:\n");
    scanf("%d",&choose);

    system("cls");
    return choose;
}

GAMEDC * produce_number_player(void)
{
    GAMEDC * Player = (GAMEDC *)malloc(sizeof(GAMEDC));
    int i;
    char ch;
    int num;

    srand(time(NULL));

    while(1){
        num = rand()%30+30;

        while(num--){
            sleep(0.1);
            system("cls");

            printf("Machine selection number generation, please wait...\n");
            for(i=0; i<LEN; i++)
                (Player->red)[i] = rand()%33 + 1;
            Player->blue = rand()%16 + 1;

            printf("Red1\tRed2\tRed3\tRed4\tRed5\tRed6\t\tBlue\n");
            print_number(Player);
        }

        printf("Use this number,yes(y) or no(n)?\n");
        scanf("%c",&ch);
        if((ch == 'y') || (ch == 'Y'))
            break;
    }
    printf("produce_number_yours:\n");
    printf("Red1\tRed2\tRed3\tRed4\tRed5\tRed6\t\tBlue\n");
    print_number(Player);
    return Player;
}

GAMEDC * input_number_player(void)
{
    GAMEDC * Player = (GAMEDC *)malloc(sizeof(GAMEDC));
    int i=0;


    for(i=0;i<LEN;i++)
    {
        printf("Please input your %d number of red,between one to thirty-three:\n",i);
        scanf("%d",&(Player->red)[i]);
    }
    printf("Please input your number of blue,between one to sixteen:\n",i);
    scanf("%d",&(Player->red)[i]);

    system("cls");
    printf("input_number_yours:\n");
    printf("Red1\tRed2\tRed3\tRed4\tRed5\tRed6\t\tBlue\n");
    print_number(Player);
    return Player;
}

GAMEDC * produce_number_rand(void)
{
    GAMEDC * Rand = (GAMEDC *)malloc(sizeof(GAMEDC));
    int i=0;

    printf("The lottery number generation, please wait...\n");
    srand(time(NULL));
    //srand(1);

    for(i=0;i<LEN;i++)
    {
        Rand->red[i] = rand()%33 + 1;
        usleep(200000);
    }
    Rand->blue = rand()%16 + 1;

    printf("produce_number_rand:\n");
    printf("Red1\tRed2\tRed3\tRed4\tRed5\tRed6\t\tBlue\n");
    print_number(Rand);
    return Rand;
}

void compare(const GAMEDC * const s1,const GAMEDC * const s2)
{
    GAMEDC * Player = (GAMEDC *)malloc(sizeof(GAMEDC));
    GAMEDC * Rand = (GAMEDC *)malloc(sizeof(GAMEDC));

    int i, j;
    int num_red = 0, num_blue = 0;

    *Player = *s1;
    *Rand = *s2;
    for(i=0; i<LEN; i++)
        for(j=0; j<LEN; j++)
            if((Player->red)[j] == Rand->red[i])
            {
                num_red++;
                (Player->red)[j] = 100;
                break;
            }
    if(Player->blue == Rand->blue)
        num_blue = 1;

    print_result(num_red,num_blue);
    return;
}

void print_result(const int num_red,const int num_blue)
{
    switch(num_blue)
    {
    case 0:
        switch(num_red)
        {
        case 4:printf("You gain fifth bonus!\n");
            break;
        case 5:printf("You gain fouth bonus!\n");
            break;
        case 6:printf("You gain second bonus!\n");
            break;
        default:printf("No take prize!\n");
            break;
        }
        break;
    case 1:
        switch(num_red)
        {
        case 3:printf("You gain fifth bonus!\n");
            break;
        case 4:printf("You gain fouth bonus!\n");
            break;
        case 5:printf("You gain third bonus!\n");
            break;
        case 6:printf("You gain first bonus!\n");
            break;
        default:printf("You gain sixth bonus!prize is 5 yuan.\n");
            break;
        }
        break;
    }
}

void print_number(GAMEDC * NUM)
{
    int i;
    for(i=0; i<LEN; i++)
    {
        if(NUM->red[i]<10)
            printf("0");
        printf("%d\t",NUM->red[i]);
    }
    printf("\t");
    if(NUM->blue<10)
            printf("0");
    printf("%d\n",NUM->blue);
}
