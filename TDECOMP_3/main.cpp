//тестовая программа    TDECOMP_1
#include <iostream>
#include "MATRIX.H"
#include <math.h>
using namespace std;
void main ()
{
	MATRIX(system);
	VECTOR(vect,4);
    float cond[4];
    float work[4];
    int ipvt[4];
// задаем столбцы матрицы
	system[0][0]=1.1;
	for (int i=0; i<4;i++){
		for (int j=0; j<4;j++){
			if (i==j) { system[i+1][j+1] = system[i][j]/10+0.9; }
			else {system[i][j]=1;}

		}}

	for (int i=0; i<4;i++){
		for (int j=0; j<4;j++){
cout<<system[i][j]<<" ";
		} cout<<endl; }

    vect[0]=10.1;
    vect[1]=9.7;
    vect[2]=7.8;
    vect[3]=7.8;


decomp(4,system,cond,ipvt,work);

    cout<<"cond="<<endl;
	cout<<cond[0]<<endl<<endl;
// число обусловленности - значение cond[0]    
solve(4,system,vect,ipvt);

    cout<<"X:"<<endl;
    for(int i=0;i<4;i++)
	{cout<<vect[i]<<endl<<endl;}


	vect[0]=1;
    vect[1]=0;
    vect[2]=0;
    vect[3]=0;
solve(4,system,vect,ipvt);

    for(int i=0;i<4;i++)
	{cout<<vect[i]<<" ";}
	cout<<endl;

    vect[0]=0;
    vect[1]=1;
    vect[2]=0;
	 vect[3]=0;

	solve(4,system,vect,ipvt);
	for(int i=0;i<4;i++)
	{cout<<vect[i]<<" ";}
	cout<<endl;

    vect[0]=0;
    vect[1]=0;
    vect[2]=1;
	vect[3]=0;
	solve(4,system,vect,ipvt);
	for(int i=0;i<4;i++)
	{cout<<vect[i]<<" ";}
	cout<<endl;

    vect[0]=0;
    vect[1]=0;
    vect[2]=0;
	vect[3]=1;
	solve(4,system,vect,ipvt);
	for(int i=0;i<4;i++)
	{cout<<vect[i]<<" ";}
	cout<<endl;


  
         }
