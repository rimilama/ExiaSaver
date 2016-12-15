#include "pbm.h"

void pbm(int *tab, int x, int y)
{
    int i = 0;
    int j = 0;
    for(;i<x;i++)
    {
        for(;j<y;j++)
        {
            if(tab[i*y+j] == '0')
            {
                tab[i*y+j] = ' ';
            }
            else
            {
                if(tab[i*y+j] == '1')
                {
                    tab[i*y+j] = '0';
                }
            }
        }
        j = 0;
    }
}

