#include <conio.h>
#include <stdio.h>
#include "vote.h"
#include "table.h"

ULONGLONG input(FILE *f, table<vote> &t);

int main()
{
   FILE *f = NULL;
   errno_t err = fopen_s(&f, "SPORT.txt", "r");

   if (f)
   {
      table<vote> t;

      ULONGLONG v_count = input(f, t);
      fclose(f);

      auto print_team_percents = [&v_count] (kv_pair<vote> item)
      {
         float k = (float) 100 / v_count; // Коэффициент, рассчитывающий процентное соотношение голосов за команду

         printf_s("%3lli | %7.2f %7.2f %7.2f\n", item.key, item.value.first * k,
                                                           item.value.last * k,
                                                           item.value.top * k);
      };

      printf_s("%2c %9s %7s %7s\n"
               "-----------------------------\n", '#', "First", "Last", "Top 3");
      t.for_each(print_team_percents);

   } else perror("Error: failed to open file.");

   return 0 * _getch() + err;
}

ULONGLONG input(FILE *f, table<vote> &t)
{
   char c = 0;
   ULONGLONG v_count = 0;
   do
   {
      for (UCHAR i = 0; i < 4; i++)
      {
         vote v;
         fscanf_s(f, "%lli", &v.team);


         if (i == 1) v.last++;
         else
         {
            v.top++;
            if (i == 0) v.first++;
         }

         vote *fv = t.find(v.team);
         if (fv != NULL)
         {
            fv->top += v.top;
            fv->last += v.last;
            fv->first += v.first;
         }
         else t.insert(v.team, v);
      }
      v_count++;
   }
   while (fscanf_s(f, "%c", &c, (UINT) sizeof c) != EOF);

   return v_count;
}