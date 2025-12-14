


#include <iostream>
#include <cmath>


using namespace std;

const double g = 9.8;
const double h = 500;

struct AIRCRAFT {
    string name;
    double m;
    double t;
    double cl;
    double cd;
    double ay;
    double time;
};



double input_par() {
    double value;
    while (!(cin >> value) || value <= 0) {
        cout << "Ошибка! Введите положительное число: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return value;
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
        cout << "Введите коэф. подъемной силы: ";
        plane[i].cl = input_par();
        cout << "Введите коэф. сопротивления: ";
        plane[i].cd = input_par();
        cout << endl;
    }
    
}

void calculating(AIRCRAFT* plane, int n, double v, double r, double s)
{
    double l;
    
    for (int i = 0; i < n; i++)
    {
        l = 0.5 * r * pow(v, 2) * s * plane[i].cl;
        plane[i].ay = (l - plane[i].m * g) / plane[i].m;
        if (plane[i].ay <= 0) {
            cout << "Самолет не наберет высоту" << endl;
            in(plane, n);
        }
        else {
            plane[i].time = sqrt(2 * h / plane[i].ay);
            cout << plane[i].name << " имеет ускорение ау= " << plane[i].ay << endl;
            cout << "Время подъема составит: " << plane[i].time << "секунд" << '\n';
        }
    }

}

void sort(AIRCRAFT* plane, int n) {
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (plane[j].time > plane[j + 1].time)
            {
                AIRCRAFT AA = plane[j];
                plane[j] = plane[j + 1];
                plane[j + 1] = AA;
                
            }
        }
    }
}

void out(AIRCRAFT* plane, int n)
{
    cout << '\n' << "Отсортированные самолеты:" << endl;
    for (int i = 0; i < n; i++)
    {
        
        cout << plane[i].name << ": ay= " << plane[i].ay << ", time = " << plane[i].time << endl;
        
    }
}

int main()
{
    int n;
    double v,r,s;
    cout << "Введите количество самолетов: ";
    cin >> n;
    cout << "Введите скорость самолетов: ";
    v = input_par();
    cout << "Введите плотность воздуха: ";
    r = input_par();
    cout << "Введите площадь крыла самолетов: ";
    s = input_par();
    AIRCRAFT* plane = new AIRCRAFT[n];
    in(plane, n);
    calculating(plane,n,v,r,s);
    sort(plane, n);
    out(plane, n);


    delete[] plane;
}
