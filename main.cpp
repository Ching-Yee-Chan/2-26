#include <cstdio>
#include <windows.h>
#include<string.h>
using namespace std ;
typedef long long ll;
const int N = 10240; // matrix size

double b[N] [N] , col_sum[N] , a[N];

void init () // generate a N*N matrix
{
    for(int i = 0; i < N; i++)
    {
        a[i] = i;
    	for (int j = 0; j < N; j++)
    	b[ i ] [ j ] = i + j ;
    }
}
void col_plain(int n)
{
    ll head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    // start time
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for (int i = 0; i < n; i++) {
        col_sum[ i ] = 0.0;
        for (int j = 0; j < n; j++)
            col_sum[ i ] += b[ j ] [ i ] * a[j];
    }
    //end time
    QueryPerformanceCounter((LARGE_INTEGER *)&tail);
    printf("%f\t", (tail-head)*1000.0/freq);
}
void col_cached(int n)
{
    ll head, tail , freq ;
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    // start time
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    for (int i = 0; i < n; i++) {
        col_sum[ i ] = 0.0;
        for (int j = 0; j < n; j++)
            for(i = 0;i < n;i++)
                col_sum[ i ] += b[ j ] [ i ] * a[j] ;
    }
    //end time
    QueryPerformanceCounter((LARGE_INTEGER *)&tail);
    printf("%f\n", (tail-head)*1000.0/freq);
}
int main()
{
    init ();
    for(int i=0;i<N;i+=10)
    {
        printf("%d\t", i);
        col_plain(i);
        col_cached(i);
    }
}
