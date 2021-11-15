#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cstring>
//#include <conio.h>
#include <time.h>
#include <omp.h>
//#include <windows.h>
#include <vector>
#include <math.h>
#include <iomanip>
#include <cstdlib>

const int n = 2000;

using namespace std;
 
void Task3MatrixDeterminant() //метод Гауса
{
    cout<<endl<<endl<<"Zadanie 3"<<endl;
    int i=0,j=0,k=0;
    //int temp;
    double det = 1;
    const double EPS = 1E-9;
    double timein, timeout, timeres = 0;
 
//  n=2;
    srand(1);
    vector <vector<double>> Matrix (n, vector<double> (n));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            Matrix[i][j] = rand()%10;            
        }
    }
    
    //Matrix[0][0] = 1;// = -1
    //Matrix[0][1] = 1;
    //Matrix[1][0] = 1;
    //Matrix[1][1] = 0;
 
/*
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    */

 
    double temp;
     for(i=0; i<n; i++)
    {
        for(j=i+1 ;j<n; j++)
        {
            if(Matrix[i][i]==0)
            {
                if(Matrix[i][j]==0)
                    temp=0;
            }
            else temp = Matrix[j][i]/Matrix[i][i];
            for(k=i; k<n; k++)
                Matrix[j][k]=Matrix[j][k]-Matrix[i][k]*temp;
        }
        det*=Matrix[i][i];
    }
/*
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << Matrix[i][j] << " ";
        }
        cout << endl;
    }
    */
 
    cout<<"Determinant: "<<det<<endl;
    
}
 
void Task3MatrixDeterminantParallel() //метод Гауса
{
    cout<<"Parallel"<<endl;
    int i=0,j=0,k=0;
    double det = 1;
    const double EPS = 1E-9;
    double timein, timeout, timeres = 0;
 
    //n=3;
    srand(1);
    vector <vector<double>> Matrix (n, vector<double> (n));
    for (int i=0;i<n;i++)
    {
        for (int j=0;j<n;j++)
        {
            Matrix[i][j] = rand()%10;            
        }
    }
    /*
    Matrix[0][0] = 2;// = -4
    Matrix[0][1] = 1;
    Matrix[0][2] = 4;
    Matrix[1][0] = 5;
    Matrix[1][1] = 3;
    Matrix[1][2] = 1;
    Matrix[2][0] = 2;
    Matrix[2][1] = 1;
    Matrix[2][2] = 0;
    */
    
    
    double temp;
 
     for(i=0; i<n; i++)
    {
        #pragma omp parallel for private(j,k,temp) shared(i)
        for(j=i+1 ;j<n; j++)
        {
            if(Matrix[i][i]==0)
            {
                if(Matrix[i][j]==0)
                    temp=0;
            }
            else temp = Matrix[j][i]/Matrix[i][i];
            
            for(k=i; k<n; k++)
                Matrix[j][k]=Matrix[j][k]-Matrix[i][k]*temp;
        }
        
    }
#pragma omp parallel for reduction(*:det)
      for(i=0; i<n; i++)
      {
        det*=Matrix[i][i];
      }
    
    //printf("%Lf ",&det);
    cout<<"Determinant: "<<det<<endl;
   
}



int main()
{
    
    //Task3MatrixDeterminant();

    Task3MatrixDeterminantParallel();
    
    return 0;
}
