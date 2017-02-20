#include <iostream>
#include <vector>
#include <stdlib.h>
#include <math.h>
#include <conio.h>
typedef double typd;
typedef long long int typ;
using namespace std;

int SprawdzWspolczynnikDeszyfrowania(typd N, typ e, typ k, typ d)
{
    if(k != 0)
    {
        typ x1, x2, delta, b ;
        typ fiN = ((e*d - 1) / k );
        if(N > fiN)
        {
            b = (N - fiN + 1);
            delta = (b*b) - (4*1*N);
            if(delta >= 0)
            {
                x1 = (b - sqrt(delta)) / 2;
                x2 = (b + sqrt(delta)) / 2;
                if(x1 * x2 == N)
                {
                cout << "Wspolczynnik deszyfrowania wynosi: " << d << endl;
                return 1;
                }
            }
        }
    }
    return 0;
}

int ObliczReduktSprawdzD(vector <typ> ulamekLancuchowy, int wielkosc, typ *Pi, typ *Qi, typd N, typ e){
	int dZnalezione = 0;
	for(int i=0;i<wielkosc;i++)
    {
		if(i==0)
        {
			Pi[i]=ulamekLancuchowy[i];
			Qi[i]=1;
		}
		else if(i==1)
		{
			Pi[i]=ulamekLancuchowy[i]*Pi[i-1]+1;
			Qi[i]=ulamekLancuchowy[i];
		}
        else
		{
			Pi[i]=ulamekLancuchowy[i]*Pi[i-1]+Pi[i-2];
			Qi[i]=ulamekLancuchowy[i]*Qi[i-1]+Qi[i-2];
		}
        typ k = Pi[i];
        typ d = Qi[i];
        dZnalezione = SprawdzWspolczynnikDeszyfrowania(N, e, k, d);
        if(dZnalezione == 1){
            return 1;
        }
    }
    if(dZnalezione == 0)
    {
        cout << "Nie znaleziono wspolczynnika deszyfrowania" << endl;
        return 0;
    }
}


vector <typ> ObliczUlamekLancuchowy(typd N, typ x)
{
	if (N < x)
	{
		typ tmp = N;
		N = x;
		x = tmp;
	}
	typ A, B;
	A = N, B = x;
	typ q = 0;
	typ redukt;
	vector <typ> ulamekLancuchowy;
	ulamekLancuchowy.push_back(0);
	while (B != 0)
	{
		typ q = (A / B);
		ulamekLancuchowy.push_back(q);
		typ tmp = A;
		A = B;
		B = tmp - q*B;
	}
    return ulamekLancuchowy;
}
int main()
{
    int i;
    typ N,e;
    cout << "Wprowadz N" << endl;
    cin >> N;
    cout << "Wprowadz e" << endl;
    cin >> e;
    vector <typ> ulamekLancuchowy;
    float granicaD = (1/3.0) * sqrt(sqrt(N));
    cout << "Wartosc, ktorej d nie moze przekroczyc aby atak zakonczyl sie powodzeniem: " << granicaD << endl;
	ulamekLancuchowy = ObliczUlamekLancuchowy(N, e);
    typ * Pi = (typ*)malloc(ulamekLancuchowy.size()*sizeof(ulamekLancuchowy));
    typ * Qi = (typ*)malloc(ulamekLancuchowy.size()*sizeof(ulamekLancuchowy));
    ObliczReduktSprawdzD(ulamekLancuchowy, ulamekLancuchowy.size(), Pi, Qi, N, e);
    getch();
}
