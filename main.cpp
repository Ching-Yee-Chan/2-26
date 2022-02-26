#include <cstdio>
#include <windows.h>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std ;
typedef long long ll;
const int N = 10230; // matrix size
const double INTERVAL = 1;

double b[N] [N] , col_sum[N] , a[N];
ofstream outfile;

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
    ll head, tail , freq ,counter(0);
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    // start time
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    tail = head;
    while(INTERVAL*freq>(tail-head)*1000)
    {
        for (int i = 0; i < n; i++)
        {
            col_sum[ i ] = 0.0;
            for (int j = 0; j < n; j++)
                col_sum[ i ] += b[ j ] [ i ] * a[j];
        }
        //end time
        QueryPerformanceCounter((LARGE_INTEGER *)&tail);
        counter++;
    }
    outfile<<(tail-head)*1000.0/freq/counter<<","<<counter<<",";
}
void col_cached(int n)
{
    ll head, tail , freq ,counter(0);
    QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
    // start time
    QueryPerformanceCounter((LARGE_INTEGER *)&head);
    while(INTERVAL*freq>(tail-head)*1000)
    {
        for (int i = 0; i < n; i++)
        {
            col_sum[ i ] = 0.0;
            for (int j = 0; j < n; j++)
                for(i = 0;i < n;i++)
                    col_sum[ i ] += b[ j ] [ i ] * a[j] ;
        }
        //end time
        QueryPerformanceCounter((LARGE_INTEGER *)&tail);
        counter++;
    }
    outfile<<(tail-head)*1000.0/freq/counter<<","<<counter<<endl;
}
int main()
{
    init ();
    outfile.open("output.txt", ios::out);
    for(int i=0;i<N;i+=10)
    {
        outfile<<i<<",";
        col_plain(i);
        col_cached(i);
    }
}
