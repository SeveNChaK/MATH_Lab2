
#include <iostream>
#include "MATRIX.H"
#include <math.h>
#include <fstream>
#include <iomanip>

#define matrixSize 4

using namespace std;


void main ()
{
MATRIX(system);
VECTOR(vect,matrixSize);
float cond[matrixSize];
float work[matrixSize];

int ipvt[matrixSize];
double d[] = {0.9f,			//�������� ������������ ���������
	0.99f,
	0.999f,
	0.9999f,
	0.99999f,
	0.999999f,
	0.9999999f,
	0.99999999f,
	0.999999999f,
	0.9999999999f,
	0.99999999999f,
	0.999999999999f,
	0.9999999999999f,
	0.99999999999999f};

//����� ������������ � ��������� ����
ofstream fout;
fout.open("out.txt");
// ������ �������� �������

for(int i = 0; i< matrixSize; i++)
	vect[i] = i + 1;
vect[3] = 5;

//�������������� ��������, ��� ���������� ����������� ��������
MATRIX(copySystem);			
VECTOR(copyVect,matrixSize);
//���������� �������
for(int q = 0; q < 14; q++)
{
	for(int z = 0; z < matrixSize; z++)
		for(int p = 0; p < matrixSize; p++){
			if(z == p){
				if(z == 0 ){
					system[z][p] = 1;
					continue;
				}
				system[z][p] = 1 + d[q];
				continue;
			}
			system[z][p] = p + 1;
		}
		for(int z = 0; z <= matrixSize; z++)
	for(int p = 0; p <= matrixSize; p++)
		copySystem[z][p] = system[z][p];

	fout<<"\n**********************\n"<<system[0][0]<<endl;
	fout<<"\r\n�������� �������:\r\n";
	for(int counti = 0; counti < matrixSize; counti++)
	{
		for(int countj = 0; countj < matrixSize; countj++)
			fout<<system[counti][countj]<<"   ";
		fout<<"\r\n";
	}
	for(int countVec = 0; countVec<matrixSize; countVec++)
		copyVect[countVec] = vect[countVec];

	decomp(matrixSize,system,cond,ipvt,work);

	fout<<"cond= ";
	fout<<cond[0]<<endl<<endl;

	// ����� ��������������� - �������� cond[0]    
	solve(matrixSize,system,vect,ipvt);

	fout<<"X1:"<<endl;
	for(int i=0;i<matrixSize;i++)
	{	
		fout<<vect[i]<<endl<<endl;
	}
	//**************************
	//��� �������� ������ �������� �������
	MATRIX(tempA);
	MATRIX(transpA);
	VECTOR(tempX,matrixSize);
	tempX[0] = 1;
	tempX[1] = 0;
	tempX[2] = 0;
	tempX[3] = 0;

	//tempA = copySystem;
	for(int counti = 0; counti < matrixSize; counti++)
		for(int countj = 0; countj < matrixSize; countj++)
			tempA[counti][countj] = copySystem[counti][countj];

	decomp(matrixSize,tempA,cond,ipvt,work);
	solve(matrixSize,tempA,tempX,ipvt);

	transpA[0][0] = tempX[0];
	transpA[0][1] = tempX[1];
	transpA[0][2] = tempX[2];
	transpA[0][3] = tempX[3];

	//*******
	tempX[0] = 0;
	tempX[1] = 1;
	tempX[2] = 0;
	tempX[3] = 0;

	//tempA = copySystem;
	for(int counti = 0; counti < matrixSize; counti++)
		for(int countj = 0; countj < matrixSize; countj++)
			tempA[counti][countj] = copySystem[counti][countj];

	decomp(matrixSize,tempA,cond,ipvt,work);
	solve(matrixSize,tempA,tempX,ipvt);

	transpA[1][0] = tempX[0];
	transpA[1][1] = tempX[1];
	transpA[1][2] = tempX[2];
	transpA[1][3] = tempX[3];

	//**********

	//tempA = copySystem;
	for(int counti = 0; counti < matrixSize; counti++)
		for(int countj = 0; countj < matrixSize; countj++)
			tempA[counti][countj] = copySystem[counti][countj];
	tempX[0] = 0;
	tempX[1] = 0;
	tempX[2] = 1;
	tempX[3] = 0;

	decomp(matrixSize,tempA,cond,ipvt,work);
	solve(matrixSize,tempA,tempX,ipvt);

	transpA[2][0] = tempX[0];
	transpA[2][1] = tempX[1];
	transpA[2][2] = tempX[2];
	transpA[2][3] = tempX[3];

	//**********

	//tempA = copySystem;
	for(int counti = 0; counti < matrixSize; counti++)
		for(int countj = 0; countj < matrixSize; countj++)
			tempA[counti][countj] = copySystem[counti][countj];
	tempX[0] = 0;
	tempX[1] = 0;
	tempX[2] = 0;
	tempX[3] = 1;

	decomp(matrixSize,tempA,cond,ipvt,work);
	solve(matrixSize,tempA,tempX,ipvt);

	transpA[3][0] = tempX[0];
	transpA[3][1] = tempX[1];
	transpA[3][2] = tempX[2];
	transpA[3][3] = tempX[3];

	double costul[4][4];
	for(int counti = 0; counti < matrixSize; counti++)
	{
		for(int countj = 0; countj < matrixSize; countj++){
			costul[counti][countj] = transpA[countj][counti];
		}
	}

	for(int counti = 0; counti < matrixSize; counti++)
	{
		for(int countj = 0; countj < matrixSize; countj++){
			transpA[counti][countj] = costul[counti][countj];
		}
	}

	fout<<"\r\n�������� �������:\r\n";
	for(int counti = 0; counti < matrixSize; counti++)
	{
		for(int countj = 0; countj < matrixSize; countj++)
			fout<<transpA[counti][countj]<<"   ";
		fout<<"\r\n";
	}
	//��� ��������� ������� �������� �������, ��������� � transpA
	//*********************************************
	//������ ���� ��������� �2
	fout<<"\r\n������ �2\r\n";

	double result_vector[matrixSize];

	for (int i = 0; i < matrixSize; i++){
		result_vector[i] = 0;
		for (int j = 0; j < matrixSize; j++){
			result_vector[i] += copyVect[j] * transpA[i][j]; }}


	fout << "X2:" << endl;
	for(int i=0;i<matrixSize;i++)
	{	
		copyVect[i] = result_vector[i];
		fout << copyVect[i] << endl << endl;
	}
	//**********************************************
	//������ ������� ������

	double chslNorm = 0;
	double znamNorm = 0;

	for(int countNorm = 0; countNorm<matrixSize; countNorm++)
	{
		copyVect[countNorm] = vect[countNorm] - copyVect[countNorm];
	}
	for(int countNorm = 0; countNorm<matrixSize; countNorm++)
		chslNorm+=(copyVect[countNorm]*copyVect[countNorm]);
	chslNorm = sqrt(chslNorm);
	fout<<"\r\n��������� = "<<chslNorm;

	for(int countNorm = 0; countNorm<matrixSize; countNorm++)
		znamNorm+=(vect[countNorm]*vect[countNorm]);
	znamNorm = sqrt(znamNorm);
	fout<<"\r\n����������� = "<<znamNorm;

	fout<<"\r\nSIGMA = "<<std::setprecision(5)<<chslNorm/znamNorm; 

}
fout.close();
}
