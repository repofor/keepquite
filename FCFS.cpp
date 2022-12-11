#include <bits/stdc++.h>
using namespace std;

class Process
{
private:
    int at;
    int bt;
    int ct;
    int tat;
    int wt;
    int Pid;

public:
    int &operator[](string var)
    {
        if (var == "at")
        {
            return at;
        }
        if (var == "bt")
        {
            return bt;
        }
        if (var == "ct")
        {
            return ct;
        }
        if (var == "tat")
        {
            return tat;
        }
        if (var == "wt")
        {
            return wt;
        }
        return Pid;
    }

    void update_after_ct()
    {
        tat = ct - at;
        wt = tat - bt;
    }

    void display()
    {
        cout << Pid << "\t" << at << "\t" << bt << "\t" << ct << "\t" << tat << "\t" << wt << endl;
    }
};
float average(vector<Process> P, string var)
{
    int total = 0;
    for (auto temp : P)
    {
        total += temp[var];
    }
    return (float)total / P.size();
}
int main()
{
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the arrival time and burst time for each process: " << endl;
    int counter = 0;
    vector<Process> P(n);
    for (Process &temp : P)
    {
        temp["id"] = counter++;
        cin >> temp["at"] >> temp["bt"];
    }
    sort(P.begin(), P.end(),
         [](Process first, Process second)
         {
             return first["at"] < second["at"];
         });
    cout << "Pid\tat\tbt\tct\ttat\twt" << endl;
    P[0]["ct"] = P[0]["at"] + P[0]["bt"];
    P[0].update_after_ct();
    P[0].display();
    for (int i = 1; i < P.size(); i++)
    {
        if (P[i]["at"] < P[i - 1]["ct"])
        {
            P[i]["ct"] = P[i - 1]["ct"] + P[i]["bt"];
        }
        else
        {
            cout << "curr['at']: " << P[i]["at"] << ", prev['ct']: " << P[i - 1]["ct"] << endl;
            P[i]["ct"] = P[i]["at"] + P[i]["bt"];
        }
        P[i].update_after_ct();
        P[i].display();
    }
    cout << "Average Waiting Time: " << average(P, "wt") << endl;
}
