#include <iostream>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <windows.h>
#include <random>
#include <fstream>


using namespace std;
void piramide(int *a,int siz);
void heap(int *a, int siz,int index);
void merg(int* a,int first,int last);
void merg_sortin(int* a,int first,int midle,int last);
void generatArray(int* a, int siz);
void swape(int* a, int* b);
 void quicksort(int* a,int first,int last);
int Partition(int *a,int first,int last);

int main()
{

    LARGE_INTEGER seed;
    QueryPerformanceCounter(&seed);
    std::mt19937 gen(seed.QuadPart);

    double freq = 0.0;
    LARGE_INTEGER x,y;
    QueryPerformanceFrequency(&x);
    freq = x.QuadPart/1.0;

    int times = 1000;
   for (std::size_t siz : {100, 1000, 10000, 100000, 1000000, 10000000}) {
        std::uniform_int_distribution<> dis(-2*siz, 2*siz);

        double merging =0 ;
        double quick =0;
        double heap =0;
        int *a = new int[siz];
         int *a2 = new int [siz];
    int *a3 = new int [siz];

        for (int n = 0 ; n < times ; n++)
        {
                generatArray(a,  siz);
  copy(a, a+siz, a2);
    copy(a, a+siz, a3);

//cout<<"Works 1"<<endl;
            QueryPerformanceCounter(&x);
            merg(a,0,siz-1);
            QueryPerformanceCounter(&y);
            std::int64_t start = x.QuadPart;

            std::int64_t end = y.QuadPart;
            merging = end - start + merging;
//cout<<"Works 2"<<endl;

            QueryPerformanceCounter(&x);
            piramide(a2,siz);
            QueryPerformanceCounter(&y);
            start = x.QuadPart;
            end = y.QuadPart;
            heap = end - start + heap;
//cout<<"Works 3"<<endl;

            QueryPerformanceCounter(&x);
            quicksort(a3,0,siz-1);
            QueryPerformanceCounter(&y);
            start = x.QuadPart;
            end = y.QuadPart;
            quick = end - start + quick;





        }

        cout  <<  setw(8) << fixed <<"For " << siz <<" elements: \n (Mergesort)time is: " << merging/freq/times << endl
              << "(Quicksort) time is: " << quick/freq/times << endl << " (Heapsort) time is: " << heap/freq/times << endl;
        delete a;


    }


    return 0;
}
void heap(int *a, int siz,int index)
{
    int largest=index;
    int left=(index*2)+1;
    int right=(index*2)+2;
    if(left<siz&&a[left]>a[largest])
        largest=left;
    if(right<siz&&a[right]>a[largest])
        largest=right;
    if(largest!=index)
    {
        swape(&a[index],&a[largest]);

        heap(a,siz,largest);
    }

}
void piramide(int *a,int siz)
{
    for(int i=siz/2-1; i>=0; i--)
        heap(a,siz,i);
    for(int i=siz-1; i>=0; i--)
    {
        swape(&a[0],&a[i]);
        heap(a,i,0);
    }

}
void merg_sortin(int* a,int first,int midle,int last)
{
    int i,j,n,size_first,size_second;
    n = first;
    size_first=midle-first+1;
    size_second=last-midle;
    int *first_array = new int [size_first];
    int *second_array = new int [size_second];
    for(i = 0; i<size_first; i++)
        first_array[i] = a[first+i];
    for(j = 0; j<size_second; j++)
        second_array[j] = a[midle+1+j];
    i = 0;
    j = 0;



    while(i<size_first && j<size_second)
    {
        if(first_array[i] <= second_array[j])
        {
            a[n]= first_array[i];
            i++;
        }
        else
        {
            a[n]=second_array[j];
            j++;
        }
        n++;
    }
    while(i<size_first)
    {
        a[n]=first_array[i];
        i++;
        n++;
    }
    while(j<size_second)
    {
        a[n]=second_array[j];
        j++;
        n++;
    }
delete []first_array;
delete []second_array;
}

void merg(int* a,int first,int last)
{
    if(first<last)
    {
        int  midle=(first+last)/2;
        merg(a,first,midle);
        merg(a,midle+1,last);
        merg_sortin(a,first,midle,last);
    }
}
int Partition(int *a,int first,int last)
{
    int i,temp;
    int value=first;
    int pivot=a[last];//should i change pivot position to midle?

    for(i=first;i<last;i++)
    {
    	if(a[i]<=pivot)
        {
            temp=a[i];
            a[i]=a[value];
            a[value]=temp;
            value++;
        }
     }

      temp=a[last];
      a[last]=a[value];
      a[value]=temp;
     return value;
 }
 void quicksort(int *a,int first,int last)
 {
    if(first<last)
    {
         int value=Partition(a,first,last);
             quicksort(a,first,value-1);
             quicksort(a,value+1,last);
    }
}





void generatArray(int* a, int siz)
{
    LARGE_INTEGER seed;
    QueryPerformanceCounter(&seed);
    std::mt19937 gen(seed.QuadPart);

    std::uniform_int_distribution<> dis(-2*siz, 2*siz);

    for (int i=0; i < siz; i++)
        a[i]=dis(gen);

}
void swape(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}
