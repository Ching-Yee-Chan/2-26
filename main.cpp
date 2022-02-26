#include <cstdio>
#include<sys/time.h>
#include<string.h>
#include<iostream>
#include<fstream>
using namespace std ;
typedef long long ll;
const int N = 10240; // matrix size
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
    timeval tv_begin, tv_end;
    int counter(0);
    // start time
    gettimeofday(&tv_begin, 0);
    tv_end = tv_begin;
    while(INTERVAL>(tv_end.tv_usec-tv_begin.tv_usec))
    {
        for (int i = 0; i < n; i++)
        {
            col_sum[ i ] = 0.0;
            for (int j = 0; j < n; j++)
                col_sum[ i ] += b[ j ] [ i ] * a[j];
        }
        //end time
        gettimeofday(&tv_end, 0);
        counter++;
    }
    outfile<<(((double)(tv_end.tv_usec-tv_begin.tv_usec))/counter<<","<<counter<<",";
}
void col_cached(int n)
{
    timeval tv_begin, tv_end;
    int counter(0);
    // start time
    gettimeofday(&tv_begin, 0);
    while(INTERVAL>(tv_end.tv_usec-tv_begin.tv_usec))
    {
        for (int i = 0; i < n; i++)
        {
            col_sum[ i ] = 0.0;
            for (int j = 0; j < n; j++)
                for(i = 0;i < n;i++)
                    col_sum[ i ] += b[ j ] [ i ] * a[j] ;
        }
        //end time
        gettimeofday(&tv_end, 0);
        counter++;
    }
    outfile<<(((double)(tv_end.tv_usec-tv_begin.tv_usec))/counter<<","<<counter<<endl;
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
