#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(0));
    FILE *Map;
    Map = fopen("1.map", "w");
    for(int i = 0; i < 40; i++){
        for(int j = 0; j < 40; j++){
            fprintf(Map, "%d:1 ", rand()%2);
        }
        if(i < 39)
            fprintf(Map, "\n");
    }
    fclose(Map);
    return 0;
}
