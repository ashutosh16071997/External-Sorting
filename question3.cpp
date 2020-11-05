#include<fstream>
#inclu\e<bits/stdc++.h>
using namespace std;
struct node {
    long long int val;
    long long int i;
};
void swap(node* x, node* y); 
  
class Minheap{
    node* arr;
    long long int size;
    public:
    Minheap(node a[],long long int size);
    void Minheapify(long long int);
    long long int left(long long int i) // to get index of left child
    {
         return (2 * i + 1);
    }
    long long int right(long long int i)  // to get index of right child
    {
          return (2 * i + 2); 
    } 
  
    // to get the root 
    node getmin()
     {
          return arr[0];
     } 
    void replace(node x) 
    { 
        arr[0] = x; 
        Minheapify(0); 
    } 
}; 

Minheap::Minheap(node a[], long long int length)
{
    size = length;
    arr = a;
    long long int k = (size - 1)/2;
    while(k>=0)
    {
        Minheapify(k);
        k--;    
    }
    
}

void Minheap::Minheapify(long long int cal)
{
    long long int l = left(cal);
    long long int r = right(cal);
    long long int small = cal;
    if(l<size && arr[l].val < arr[cal].val)
    {
        small = l;
    }
    if(r<size && arr[r].val < arr[small].val)
    {
        small = r;
    }
    if(small != cal)
    {
        swap(&arr[cal], &arr[small]); 
        Minheapify(small); 
    }
}
void swap(node* x, node* y) 
{ 
    node temp = *x; 
    *x = *y; 
    *y = temp; 
} 
void merge(long long int arr[],long long int l,long long int m,long long int r)
{
    long long int i,j,k;
    long long int size1 = m - l + 1;
    long long int size2 = r - m;
    vector<long long int> LEFT(size1);
    vector<long long int> RIGHT(size2);
    i = 0;
    while(i<size1)
    {
        LEFT[i] = arr[i+l];
        i++;
    }
    j = 0;
    while(j<size2)
    {
        RIGHT[j] = arr[m+1+j];
        j++;
    }
    i = 0; j = 0; k = l;
    for(;i<size1 && j<size2;)
    {
        if(LEFT[i]<=RIGHT[j])
        {
            arr[k++] = LEFT[i++];
        }
        else if (LEFT[i]>RIGHT[j])
        {
            arr[k++] = RIGHT[j++];
        }
        
    }
    while(i<size1)
    {
        arr[k++] = LEFT[i++];
    }
    while(j<size2)
    {
        arr[k++] = RIGHT[j++];
    }
}
void mergesort(long long int brr[],long long int l,long long int r)
{
    if(l<r)
    {
       long long  int m = l+(r-l)/2;
        mergesort(brr,l,m);
        mergesort(brr,m+1,r);
        merge(brr,l,m,r);
    }
}
FILE* openFile(char* fileName, char* mode) 
{ 
	FILE* fp = fopen(fileName, mode); 
	if (fp == NULL) { 
		perror("Error while opening the file.\n"); 
		exit(EXIT_FAILURE); 
	} 
	return fp; 
} 
void mergefiles(char* output_file, long long int n, long long int k)
{
    FILE* in[k];
    long long int i = 0;
    while(i<k)
    {
        char filename[4];
        snprintf(filename,sizeof(filename),"%lld",i);
        char readArr[] ="r";
		char *rd = readArr;
		in[i] = openFile(filename, rd); 
        i++;
    }
    char outArr[] ="w";
	char *wr = outArr;
    FILE* fpp = openFile(output_file, wr);
    node* parr = new node[k];
    i = 0;
    while(i<k)
    {
        if(fscanf(in[i],"%lld ",&parr[i].val) != 1)
        break;
        parr[i].i = i;
        i++;
    }
    Minheap heapp(parr,i);
    long long int count = 0;
    for(;count != i;)
    {
        node root = heapp.getmin();
        fprintf(fpp,"%lld,",root.val);
        if(fscanf(in[root.i],"%lld ",&root.val)!= 1)
        {
            root.val = INT_MAX;
            count++;
        }
        heapp.replace(root);
    }
    long long int x = 0;
    while(x<k)
    {
        fclose(in[x]);
        x++;
    }
    fclose(fpp);
}
void chunkcreater(long long int runsize,long long int ways,char* inputfile)
{
   
    FILE* out[ways];
    char filename[4];
    char readArr[] ="r";
	char *rd = readArr;
    FILE* in = openFile(inputfile, rd);
    long long int i = 0;
    while(i<ways)
    {
        snprintf(filename,sizeof(filename),"%lld",i);
       
         char outArr[] ="w";
		char *wr = outArr;
        out[i] = openFile(filename,wr);
        i++;
    }
    long long int *zrr = (long long int *)malloc(runsize*sizeof(long long int));
    bool flag = true;
     int nextout = 0;
    while(true)
    {   
        i = 0;
        while(i<runsize)
        {   
           if (fscanf(in, "%lld,", &zrr[i]) != 1) { 

                flag = false; 
                break; 
                }
            i++;
        }
        mergesort(zrr,0,i-1);
       long long  int j = 0;
        while(j<i)
        {
            fprintf(out[nextout],"%lld ",zrr[j]);
            j++;
        }
        nextout++;
        if(!flag)
        break;
    }
    long long int m = 0;
    while(m<ways)
    {
        fclose(out[m]);
        m++;
    }
    fclose(in);
}
int main()
{
      int number = 1;
      char outputfile[] = "output.txt";
      char inputfile[] = "input.txt";
    long long int memsize = 500000000;
    long long int ways;
    long long int chunksize = memsize;
    FILE *f;
    f = fopen("input.txt" , "r");
    fseek(f, 0, SEEK_END);
    long long length = (unsigned long)ftell(f);
	ways = ceil(length / (chunksize*1.0));
    fclose(f);
    chunkcreater(chunksize,ways,inputfile);
    
    mergefiles(outputfile,chunksize,ways);
    std::ifstream fileIn( "output.txt" );              // Open for reading
    std::string contents;
    fileIn >> contents;                              // Store contents in a std::string
    fileIn.close();
    contents.pop_back();                             // Remove last character
    std::ofstream fileOut( "file.txt", std::ios::trunc ); // Open for writing (while also clearing file)
    fileOut << contents;                             // Output contents with removed character
    fileOut.close();
    return 0;
}