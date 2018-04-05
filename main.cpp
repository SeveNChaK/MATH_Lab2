#include <iostream>
#include <cmath>
#include "TDECOMP_1/MATRIX.CPP"

//РАСЧЕТ К-ОЙ СТРОЧКИ ПРАВОЙ ЧАСТИ УРАВНЕНИЯ
float getB(float k) {
    return powf(2, k) + cosf(((k * (float) M_PI) / 360));
}

int main() {
    int N[3] = {5, 7, 9}; //Заданные значения N

    for (int n = 0; n < 3; n++) {
        int m_size = N[n]; //Исследуемое N

        MATRIX(matrix); //Исследуемая матрица
        float cond[m_size];
        float work[m_size];
        int ipvt[m_size];

        float b[m_size]; //Исследуемая правая часть уравнения, в конце здесь будет храниться ответ

        //ЗАПОЛНЕНИЕ МАТРИЦЫ
        for (int i = 0; i < m_size; i++) {
            for (int j = 0; j < m_size; j++) {
                if (i == 0) {
                    matrix[i][j] = 1;
                    printf("%.1f\t", matrix[i][j]);
                } else if (j == m_size - 1) {
                    matrix[i][j] = powf(1 + powf(0.1, i), i);
                    printf("%.5f\t", matrix[i][j]);
                } else {
                    matrix[i][j] = powf(j + 1, i);
                    printf("%.1f\t", matrix[i][j]);
                }
            }
            //ВЫЧИСЛЕНИЕ ПРАВОЙ ЧАСТИ УРАВНЕНИЯ
            b[i] = getB(i + 1);
            //printf("\n");
            printf("\t\tb = %.5f\n", b[i]);
        }

        printf("\n");

        //НАХОЖДЕНИЕ РЕШЕНИЯ УРАВНЕНИЯ
        decomp(m_size, matrix, cond, ipvt, work);
        solve(m_size, matrix, b, ipvt);
        float result = 0;
        for (int k = 0; k <m_size; k++) {
            result+=cond[k];
        }
        printf("cond = %.10f\n", result);

        //ВЫВОД РЕШЕНИЯ
        for (int i = 0; i < m_size; i++) {
            printf("%.10f\n", b[i]);
        }

        printf("\n");
        printf("\n");
        printf("\n");
    }

    return 0;
}