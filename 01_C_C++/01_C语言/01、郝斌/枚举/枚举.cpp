# include <stdio.h>
enum Weekday
{
	Monday,Tuesday,Wednesday=7,Tursday,Firday,Saturday,Sunday
};

int main(void)
{
	enum Weekday day=Sunday;
	printf("%d\n",day);

	return 0;
}