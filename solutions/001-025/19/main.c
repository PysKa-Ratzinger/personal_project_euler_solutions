#include <stdio.h>

struct date{
  int year;
  int month;
  int day;
  int day_of_week;
};

int dom[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
char *doms[] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Satudary"};

int is_leap_year(int year){
  return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
}

int days_of_month(struct date *date, int month){
  if(month == 2 && is_leap_year(date->year)){
    return 29;
  }else{
    return dom[month-1];
  }
}

void add_days(struct date *date, int num_days){
  date->day += num_days;
  date->day_of_week = (date->day_of_week + num_days) % 7;
  int temp = days_of_month(date, date->month);
  if(date->day > temp){
    date->day -= temp;
    date->month++;
    if(date->month > 12){
      date->month = 1;
      date->year++;
    }
  }
}

int main(){
  struct date date;
  date.year = 1900;
  date.month = 1;
  date.day = 1;
  date.day_of_week = 1;

  int res = 0;

  add_days(&date, 6);
  while(date.year < 2001){
    if(date.year >= 1901 && date.day == 1){
      printf("Date: %02d/%02d/%04d - %s\n", date.day, date.month, date.year, doms[date.day_of_week]);
      res++;
    }
    add_days(&date, 7);
  }

  printf("If you can trust me, the result you are looking for is %d.\n", res);
  return 0;
}

