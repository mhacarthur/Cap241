
#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

using namespace std;  

// Para ejecutar en una linea
// g++ Strip_Tree.cpp -o out && ./out

// Para obtener el minimo
double minimo(double a[],int len)
{
    double min = a[0]; 
    for (int i = 1; i < len; i++) 
    { 
        if (a[i] < min)
        {
            min = a[i]; 
        }       
    } 
    return min;
}

// Para obtener el maximo
double maximo(double a[],int len)
{
    double max = a[0];

    for (int i = 1; i < len; i++)
    {
        if (a[i] > max)
        {
            max = a[i];
        }
    }
    return max;
}

// Strip Tree 
double **Strip_Tree(double x[],double y[],int len, int res)
{
    int a,N,Num_rectangulo;
    int i,j;
    double x1,y1,x2,y2;

    Num_rectangulo = (len - 2 )/res;

    int aa = len;

    N = Num_rectangulo-2;

    // Creando la matriz salida que tendra toda la informacion sobre los rectangulos
    // Sera inicialmente una matriz de ceros
    // salida[tiempo][metricas]

    double **salida;
    salida = new double*[12];

    for(i=0; i<Num_rectangulo; i++) {
        salida[i] = new double[Num_rectangulo];
    }

    //for(i=0; i<N; i++) {
    //    for(i=0; i<N; i++) {
    //        salida[i][j] = 0;
    //    }    
    //}


    for(int ii=1; ii<3; ii++)
    {

        int dim = len - (ii-1)*res;

        //cout << dim << endl;   

        double x_new[dim];
        double y_new[dim];

        double x1[res+1];
        double y1[res+1];

        int dif = len - res;

        double x2[dif];
        double y2[dif];

        int a = 0;
        for(i=(ii-1)*res; i<len; i++)
        {
            x_new[a] = x[i];
            y_new[a] = y[i];
            a = a + 1;
        }

        //x1 = x_new[0:res+1]
        //y1 = y_new[0:res+1]

        a = 0;
        for(i=0; i<res+2; i++)
        {
            x1[a] = x_new[i];
            y1[a] = y_new[i];
            a = a + 1;
        }

        a = 0;
        for(i=res; i<len; i++)
        {
            x2[a] = x_new[i];
            y2[a] = y_new[i];
            a = a +1;
        }

        //for(i=0; i<res+1; i++)
        //{
        //   cout << x1[i] << "," << y1[i] << endl;
        //}

        // Primera parte
        double x1_start = x1[0];
        double x1_end = x1[res];

        double y1_start = y1[0];
        double y1_end = y1[res];

        //cout << " " << endl;
        //cout << x1_start << "," << x1_end << endl;
        //cout << x2_start << "," << x2_end << endl;

        // Pendiente
        double m1 = (y1_end - y1_start)/(x1_end - x1_start);

        double x1s = x1_start;
        double y1s = y1_start;

        double x1e = x1_end;
        double y1e = y1_end;

        double lon1 = sqrt( ((x1e-x1s)*(x1e-x1s)) + ((y1e-y1s)*(y1e-y1s)) );

        //cout << m1 << "," << lon1 << endl;

        // Segunda parte
        double x2_start = x2[0];
        double x2_end = x2[len-res];

        double y2_start = y2[0];
        double y2_end = y2[len-res];

        cout << " " << endl;
        cout << x2_start << "," << x2_end << endl;
        cout << x2_end << "," << y2_end << endl;

        // Pendiente
        double m2 = (y2_end - y2_start)/(x2_end - x2_start);

        double x2s = x2_start;
        double y2s = y2_start;

        double x2e = x2_end;
        double y2e = y2_end;

        double lon2 = sqrt( ((x2e-x2s)*(x2e-x2s)) + ((y2e-y2s)*(y2e-y2s)) );

        //cout << m2 << "," << lon2 << endl;

        //double test = minimo(y2,dif);

        double wr = y2s - minimo(y2,dif);
        double wl = maximo(y2,dif) - y2s;

        //cout << wr << "," << wl << endl;

        // Insertando los valores en la matriz salida
        salida[ii-1][0] = x1s;
        salida[ii-1][0] = x1s;
        salida[ii-1][1] = y1s; 
        salida[ii-1][2] = x1e;
        salida[ii-1][3] = y1e;
        salida[ii-1][4] = x2s;
        salida[ii-1][5] = y2s;
        salida[ii-1][6] = x2e;
        salida[ii-1][7] = y2e;
        salida[ii-1][8] = wl;
        salida[ii-1][9] = wr;
        salida[ii-1][10] = lon1;
        salida[ii-1][11] = lon2;
         
    }

    return salida;

}

int main(){

    int i;
    double x[41];
    double y[41];

    // Funcion cuadratica
    int a = -20;
    for(i=0;i<41;++i)
    {
        x[i] = a;
        y[i] = x[i] * x[i];

        a = a + 1;
    }

    double len_x = sizeof(x) / sizeof(*x);
    double len_y = sizeof(y) / sizeof(*y);

    double min_x = minimo(x,len_x);
    double max_x = maximo(x,len_x);

    double min_y = minimo(y,len_y);
    double max_y = maximo(y,len_y);

    double **mat = Strip_Tree(x,y,len_x,1);

    //for(i=0; i<3; i++)
    //{
    //    cout<<mat[i][0]<<","<<mat[i][1]<<","<<mat[i][2]<<","<<mat[i][3]<<","<<mat[i][4]<<","<<mat[i][5]<<","<<mat[i][6]<<","<<mat[i][7]<<","<<mat[i][8]<<endl;
    //}

    cout << " " << endl;
    cout<<mat[0][0]<<","<<mat[0][1]<<","<<mat[0][2]<<","<<mat[0][3]<<","<<mat[0][4]<<","<<mat[0][5]<<","<<mat[0][6]<<","<<mat[0][7]<<","<<mat[0][8]<<","<<mat[0][9]<<endl;

    return 0;

}