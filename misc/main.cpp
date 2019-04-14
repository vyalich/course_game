#include <cstdio>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(0));
    FILE *Map;
    Map = fopen("1.map", "w");
    for(int i = 0; i < 80; i++){
        if(i>=5 && i <75){
            for(int j = 0; j < 5; j++){
                fprintf(Map, "0:1 ");
            }
            for(int j =5; j < 75; j++){
                fprintf(Map, "1:1 ");
            }
            for(int j = 75; j < 80; j++){
                fprintf(Map, "0:1 ");
            }
        }
        else{
            for(int j = 0; j < 80; j++){
                fprintf(Map, "0:1 ");
            }
        }
        if(i < 39)
            fprintf(Map, "\n");
    }
    fclose(Map);
    return 0;
}
