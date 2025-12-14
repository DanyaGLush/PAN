

#include <iostream>
#include <cmath>

using namespace std;

struct AIRCRAFT {
    string name;
    double m;
    double t;
    double s;
    double cl;
    double cd;
    double l;
    double d;
    double a;
};

double input_par()
{
    double num;
    while (!(cin >> num) || num <= 0)
    {
        cout << "Ошибка!!! Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return num;
}
void in(AIRCRAFT* plane, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Введите самолет: " << endl;
        cout << "Введите название самолета: ";
        cin >> plane[i].name;
        cout << "Введите массу самолета: ";
        plane[i].m = input_par();
        cout << "Введите тягу самолета: ";
        plane[i].t = input_par();
        cout << "Введите площадь крыла самолета: ";
        plane[i].s = input_par();
        cout << "Введите коэф. подъемной силы: ";
        plane[i].cl = input_par();
        cout << "Введите коэф. сопротивления: ";
        plane[i].cd = input_par();
        cout << endl;
    }

}
void calculating(AIRCRAFT* plane, int n, double v, double r)
{
    
    for (int i = 0; i < n; i++)
    {
        plane[i].l = 0.5 * r * pow(v, 2) * plane[i].s * plane[i].cl;
        plane[i].d= 0.5 * r * pow(v, 2) * plane[i].s * plane[i].cd;
        plane[i].a = (plane[i].t - plane[i].d) / plane[i].m;
    }

}
int find_max(AIRCRAFT* plane, int n)
{
    double g = abs(plane[0].a);
    int c=0;
    for (int i = 1; i < n; i++)
    {
        if (abs(plane[i].a) > g) {
            g = abs(plane[i].a);
            c = i;
        }
    }
    return c;
}

void out(AIRCRAFT* plane, int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << "Самолет " << plane[i].name << ":" << endl;
        cout << "Подъемная сила: " << plane[i].l << endl;
        cout << "Сила сопротивления: " << plane[i].d << endl;
        cout << "Ускорение: " << plane[i].a << endl;
    }
}
//𝐿 = 12𝜌𝑉2𝑆𝐶𝐿 - подъемная сила 
//𝐿 = 12𝜌𝑉2𝑆𝐶𝐷 - сопротивление
//𝑎 = 𝑇−𝐷𝑚 - ускорение
int main()
{
    int n,i;
    double v, r, s;
    cout << "Введите количество самолетов: ";
    cin >> n;
    cout << "Введите скорость самолетов: ";
    v = input_par();
    cout << "Введите плотность воздуха: ";
    r = input_par();
    AIRCRAFT* plane = new AIRCRAFT[n];
    in(plane, n);
    calculating(plane, n, v, r);
    out(plane, n);
    i = find_max(plane, n);
    cout << "Самое большое ускорение по модулю имеет самолет " << plane[i].name << " | a = " << plane[i].a << endl;
    delete[] plane;
}


