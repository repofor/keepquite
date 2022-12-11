#include <bits/stdc++.h>
using namespace std;

class os_phase1
{
public:
    int index = 0;
    char M[100][4], IR[4], R[4], buffer[40], temp_buff[4];
    int i, C, IC, SI = 0, loc;
    // int time = 0;
    vector<string> EM{"No Error", "Out of Data", "Line Limit Exceeded",
                      "Time Limit Exceeded", "Operation Code Error", "Operand Error", "Invalid Page Fault"};
    vector<int> rnumbers;
    vector<string> lines;
    ifstream ip_file;
    ofstream op_file;
    string line;

    os_phase1()
    {
        for (i = 0; i < 29; i++)
        {
            rnumbers.push_back(i);
        }
    }


    void init()
    {
        int i, j;

        // Initialize external memory
        for (i = 0; i < 100; i++)
            for (j = 0; j < 4; j++)
                M[i][j] = '*';

        // Initialize GPR and IR
        for (i = 0; i < 4; i++)
            IR[i] = R[i] = '*';

        // Initialize counter to 0
        C = IC = SI = 0;
    }

//clears the buffer
    void clear()
    {
        int i;
        for (i = 0; i < 40; i++)
        {
            buffer[i] = '\0';
        }
    }

//reads a line from input file and store in buffer
    void read()
    {
        char c;
        int i = 0;
        clear();

        do
        {
            ip_file.get(c);
            buffer[i] = c;
            i++;
        } while (c != '\n');
    }

    void Read()
    {
        int i, j, k;
        read();
        i = loc;
        k = 0;
        while (i < loc + 10)
        {
            j = 0;
            while (j < 4 && buffer[k] != '\0')
            {
                M[i][j] = buffer[k];
                k++;
                j++;
            }
            i++;
        }
    }

    int location()
    {
        return ((int)IR[2] - 48) * 10 + ((int)IR[3] - 48);
    }

    void Write()
    {
        int i, j, k;
        IR[3] = '0';
        k = 0;

        clear();
        i = loc;
        while (i < loc + 10)
        {
            j = 0;
            while (j < 4 && M[i][j] != '*')
            {
                if (M[i][j] == '\n')
                    buffer[k] = ' ';

                else
                    buffer[k] = M[i][j];

                k++;
                j++;
            }
            i++;
        }

        buffer[k] = '\n';
        i = 0;

        while (buffer[i] != '\n')
        {
            op_file.put(buffer[i]);
            i++;
        }
        op_file << '\n';
    }

    void Terminate()
    {
        if (!op_file.is_open())
        {
            op_file.open("output.txt", ios::app);
        }
        op_file << "\n\n";
        op_file.close();

        load();
    }

    void Execute()
    {
        do
        {
            IR[0] = M[IC][0]; // RA = 110
            IR[1] = M[IC][1];
            IR[2] = M[IC][2];
            IR[3] = M[IC][3];

            loc = location();

            IC++;

            if (IR[0] == 'L' && IR[1] == 'R')
            {
                R[0] = M[loc][0];
                R[1] = M[loc][1];
                R[2] = M[loc][2];
                R[3] = M[loc][3];

            }

            else if (IR[0] == 'S' && IR[1] == 'R')
            {
                M[loc][0] = R[0];
                M[loc][1] = R[1];
                M[loc][2] = R[2];
                M[loc][3] = R[3];
            }

            else if (IR[0] == 'C' && IR[1] == 'R')
            {
                if (R[0] == M[loc][0] && R[1] == M[loc][1] && R[2] == M[loc][2] && R[3] == M[loc][3])
                    C = 1;
                else
                    C = 0;
            }

            else if (IR[0] == 'B' && IR[1] == 'T')
            {
                if (C == 1)
                    IC = loc;
            }

            else if (IR[0] == 'G' && IR[1] == 'D')
            {
                SI = 1;
                MOS();
            }

            else if (IR[0] == 'P' && IR[1] == 'D')
            {
                SI = 2;
                MOS();
            }

            else if (IR[0] == 'H')
            {
                SI = 3;
                MOS();
            }

        } while (IR[0] != 'H');
    }

    void startExecution()
    {
        IC = 0;
        Execute();
    }

    void MOS()
    {
        if(SI==1){
            Read();
        }
        else if(SI==2){
            Write();
        }
        else if(SI==3){
            Terminate();
        }
    }


    void load()
    {
        int block = 0, a = 0, i, j;

        while (!ip_file.eof())
        {
            read();
            index++;

            if (buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
            {
                init();
                continue;
            }

            else if (buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
            {
                startExecution();
            }

            else if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
            {
                continue;
            }

            //Program Card
            else
            {
                int a=0;
                for (int i = 0; i < 10; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        M[i][j] = buffer[a++];
                    }
                }
            }
        }
    }

};

int main()
{
    os_phase1 obj;
    obj.ip_file.open("input.txt");
    obj.op_file.open("output.txt", ios::out | ios::trunc);
    obj.load();
    obj.ip_file.close();
    obj.op_file.close();
    return 0;
}