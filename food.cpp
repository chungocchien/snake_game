#include"header.h"

void khoi_tao(food_ &a)
{
    a.x=0+rand()%((680+1-0)/20)*20;
    if((a.x>=0&&a.x<=40)||(a.x>=620&&a.x<=680)||(a.x>=260&&a.x<=400)) {a.y=0+rand()%((640+1-0)/20)*20;}
    if((a.x==60)||(a.x==600))
        {
            for(int k=0;k<1000;k++)
            {
                a.y=0+rand()%((640+1-0)/20)*20;
                if((a.y>=60&&a.y<=240)||(a.y>=380&&a.y<=560)) continue;
                if((a.y>=0&&a.y<=40)||(a.y>=260&&a.y<=360)||(a.y>=580&&a.y<=640)) break;
            }

        }
    if((a.x>=80&&a.x<=240)||(a.x>=420&&a.x<=580))
    {
        for(int i=0;i<1000;i++)
            {
                a.y=0+rand()%((640+1-0)/20)*20;
                if(a.y==60||a.y==560) {continue;}
                else {break;}
            }
    }
}

