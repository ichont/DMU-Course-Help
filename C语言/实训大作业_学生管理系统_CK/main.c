#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Student.c" //????????????
int main()
{
int id;
memset(Head,0,sizeof(STU)*(N+1)); //?????????
while(1) {                        //??????
    menu();
    scanf("%d",&id);
    switch(id) {                  //????id??????
        case 1:
            Input(Head);
            break;
        case 2:
            Loadstudent(Head,N);
            break;
        case 3:
            Show();
            break;
        case 4:
            FindnStudent();
            break;
        case 5:
            Findscore();
            break;
        case 6:
            Maxscore();
            break;
        case 7:
            Choosesort();
            break;
        case 8:
            Bubblesort();
            break;
        case 9:
            Save(Head,N);
            break;
        case 10:
            Insertsort();
            break;
        case 0:
            return 0;
            break;
        default:
            printf("????????!!!!\n");
            system("cls");       //????
    }
  }
         return 0;
}
