#include <bits/stdc++.h>
using namespace std;

class PCB
{
public:
    int job_id, ttl, tll, ttc, llc;
};

class os_phase2
{
public:
    int index = 0;
    char M[300][4], IR[4], R[4], buffer[40], temp_buff[4];
    int i, C, IC, VA, RA, PTR, SI = 0, TI = 0, PI = 0, loc, PTE, temp_loc;
    PCB pcb;
    // int time = 0;
    vector<string> EM{"No Error", "Out of Data", "Line Limit Exceeded",
                      "Time Limit Exceeded", "Operation Code Error", "Operand Error", "Invalid Page Fault"};
    vector<int> rnumbers;
    vector<string> lines;
    ifstream ip_file;
    ofstream op_file;
    string line;

    os_phase2()
    {
        for (i = 0; i < 29; i++)
        {
            rnumbers.push_back(i);
        }
    }

    int random()
    {
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        shuffle(rnumbers.begin(), rnumbers.end(), default_random_engine(seed));

        int r = rnumbers[0];
        rnumbers.erase(rnumbers.begin());
        return r * 10;
    }

    void init()
    {
        int i, j;

        // Initialize external memory
        for (i = 0; i < 300; i++)
            for (j = 0; j < 4; j++)
                M[i][j] = '*';

        // Initialize GPR and IR
        for (i = 0; i < 4; i++)
            IR[i] = R[i] = '*';

        // Initialize counter to 0
        C = IC = SI = TI = PI = PTR = 0;
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
        pcb.llc++;
        if (pcb.llc > pcb.tll)
        {
            Terminate(2);
        }

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

    void Terminate(int n)
    {
        if (!op_file.is_open())
        {
            op_file.open("output.txt", ios::app);
        }
        op_file <<EM[n] << "\n";
        op_file << "\n\n";
        op_file.close();

        exit(0);
    }

    void operations()
    {
        switch (SI)
        {
        case 1:
            Read();
            break;

        case 2:
            Write();
            break;

        case 3:
            Terminate(0);
            break;
        }
    }

    void Execute()
    {
        addressMap(IC);
        do
        {
            IR[0] = M[RA][0]; // RA = 110
            IR[1] = M[RA][1];
            IR[2] = M[RA][2];
            IR[3] = M[RA][3];

            loc = location();

            IC++;

            if (IR[0] == 'L' && IR[1] == 'R')
            {
                pcb.ttc++;
                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                    MOS();
                }
                R[0] = M[loc][0];
                R[1] = M[loc][1];
                R[2] = M[loc][2];
                R[3] = M[loc][3];

                RA++;
            }

            else if (IR[0] == 'S' && IR[1] == 'R')
            {
                pcb.ttc += 2;
                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                    MOS();
                }
                M[loc][0] = R[0];
                M[loc][1] = R[1];
                M[loc][2] = R[2];
                M[loc][3] = R[3];
                RA++;
            }

            else if (IR[0] == 'C' && IR[1] == 'R')
            {
                pcb.ttc++;
                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                    MOS();
                }
                if (R[0] == M[loc][0] && R[1] == M[loc][1] && R[2] == M[loc][2] && R[3] == M[loc][3])
                    C = 1;
                else
                    C = 0;
                RA++;
            }

            else if (IR[0] == 'B' && IR[1] == 'T')
            {
                pcb.ttc++;
                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                    MOS();
                }
                if (C == 1)
                    IC = loc;
                RA++;
            }

            else if (IR[0] == 'G' && IR[1] == 'D')
            {
                SI = 1;
                VA = (IR[2] - '0') * 10 + (IR[3] - '0');

                if (!(IR[2] <= 57 && IR[3] <= 57)) // to check oprand error
                {
                    PI = 2;
                }
                // if (PTE == VA)
                //     allocate();
                // addressMap(count);
                RA++;
                pcb.ttc += 2;
                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                }
                MOS();
            }

            else if (IR[0] == 'P' && IR[1] == 'D')
            {
                SI = 2;
                pcb.ttc++;
                if (IR[2] <= 57 && IR[3] <= 57) // to check oprand error
                {
                    int temp = (IR[2] - '0') * 10 + (IR[3] - '0');
                    if (M[temp][0] == '*')
                    {
                        PI = 3;
                    }
                    else
                    {
                        RA++;
                    }
                }
                else
                {
                    PI = 2;
                }

                if (pcb.ttc > pcb.ttl)
                {
                    TI = 2;
                }
                MOS();
            }

            else if (IR[0] == 'H')
            {
                SI = 3;
                MOS();
            }

            else
            {
                // operation code error
                PI = 1;
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
        if (PI == 1 && TI == 0)
        {
            Terminate(4);
        }
        else if (PI == 2 && TI == 0)
        {
            Terminate(5);
        }
        else if (PI == 3 && TI == 0)
        {
            Terminate(6);
            // More code to be added
        }
        else if (PI == 1 && TI == 2)
        {
            Terminate(3);
            Terminate(4);
        }
        else if (PI == 2 && TI == 2)
        {
            Terminate(3);
            Terminate(5);
        }
        else if (PI == 3 && TI == 2)
        {
            Terminate(3);
        }

        else if (SI == 1 && TI == 0)
        {
            Read();
            if (buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
            {
                cout << "Out of data error" << endl;
                Terminate(1);
            }
        }
        else if (SI == 2 && TI == 0)
        {
            Write();
        }
        else if (SI == 3 && TI == 0)
        {
            Terminate(0);
        }
        else if (SI == 1 && TI == 2)
        {
            Terminate(3);
        }
        else if (SI == 2 && TI == 2)
        {
            Write();
            Terminate(3);
        }
        else if (SI == 3 && TI == 2)
        {
            Terminate(0);
        }
    }
    
    //Get Frame for page table randomly
    void allocate()
    {
        PTR = random();
        for (int i = PTR; i < PTR + 10; i++)
            for (int j = 0; j < 4; j++)
                M[i][j] = '#';

        //Allocate frame Frame number for first line
        temp_loc = random() / 10; // 11
        M[PTR][2] = temp_loc / 10 + '0';
        M[PTR][3] = temp_loc % 10 + '0';
    }

    void pcb_init()
    {
        pcb.job_id = (buffer[4] - '0') * 1000 + (buffer[5] - '0') * 100 + (buffer[6] - '0') * 10 + (buffer[7] - '0');
        pcb.llc = 0;
        pcb.ttc = 0;
        pcb.ttl = (buffer[8] - '0') * 1000 + (buffer[9] - '0') * 100 + (buffer[10] - '0') * 10 + (buffer[11] - '0');
        pcb.tll = (buffer[12] - '0') * 1000 + (buffer[13] - '0') * 100 + (buffer[14] - '0') * 10 + (buffer[15] - '0');
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
                pcb_init();
                allocate();
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
                int a = 0;
                if (M[temp_loc * 10][0] != '*')
                    temp_loc++;

                for (int i = temp_loc * 10; i < (temp_loc * 10) + 10; i++)
                {
                    for (int j = 0; j < 4; j++)
                    {
                        M[i][j] = buffer[a++];
                    }
                }
            }
        }
    }

    void addressMap(int VA)
    {
        PTE = PTR + VA / 10;
        int n = (M[PTE][2] - '0') * 10 + (M[PTE][3] - '0');
        RA = (n * 10) + VA % 10; // 110
    }
};

int main()
{
    os_phase2 obj;
    obj.ip_file.open("input.txt");
    obj.op_file.open("output.txt", ios::out | ios::trunc);
    obj.load();
    obj.ip_file.close();
    obj.op_file.close();
    return 0;
}