#include<iostream>
#include<fstream>
using namespace std;


class OS{
    private:
        char M[100][4];     
        char IR[4];      
        char R[4];          
        int IC;           
        int SI;             
        bool C;            
        char buffer[44];

    public:
        void init();
        void LOAD();
        void Execute();
        void MOS();

        fstream infile;
        fstream outfile;
};



void OS::init()
{

    for(int i = 0; i<100; i++)
    {
        for(int j = 0; j<4; j++ )
        {
            M[i][j]=' ';

        }

    }


    IR[0] = {' '};
    R[0] = {' '};
    C = false;

}


void OS::MOS()
{

    if(SI == 1)     //Read Mode
    {
        for(int i=0;i<=40;i++)
           buffer[i]='\0';

        infile.getline(buffer,44);
        for(int k=0;k<=40;k++)
           cout<<buffer[k];
        cout << "\n";

        int k = 0;
        int i = IR[2]-48;
        i = i*10;


        for( int l=0 ; l<10 ;  ++l)
        {
            for(int j = 0 ; j<4; ++j)
            {
                M[i][j] = buffer[k];
                k++;
            }
            if(k == 40)
            {
                break;
            }
            i++;
        }

        for(int i = 0; i<100; i++)
        {
            cout<<"M["<<i<<"]\t";
            for(int j = 0; j<4; j++ )
            {
                cout<<M[i][j];
            }
            cout<<endl;
        }
    }
    else if(SI == 2)        //Write Mode
    {
      for(int i=0;i<=40;i++)
           buffer[i]='\0';

        int k = 0;
        int i = IR[2]-48;
        i = i*10;


        for( int l=0 ; l<10 ;  ++l)
        {
            for(int j = 0 ; j<4; ++j)
            {
                buffer[k]=M[i][j];
                outfile<<buffer[k];

                k++;
            }
            if(k == 40)
            {
                break;
            }
            i++;
        }
        //    for(int i = 0; i<100; i++)
        // {
        //     cout<<"M["<<i<<"]\t";
        //     for(int j = 0; j<4; j++ )
        //     {
        //         cout<<M[i][j];
        //     }
        //     cout<<endl;
        // }

        outfile<<"\n";

    }
    else if(SI == 3)        //Terminate
    {

        outfile<<"\n";
        outfile<<"\n";

    }

}



//Execution
void OS::Execute()
{
    while(true)
    {
        for(int i = 0; i<4; i++)        //Load in register
        {
            IR[i] = M[IC][i];
        }
        IC++;

        if(IR[0] == 'G' && IR[1] == 'D')    //GD
        {
            SI = 1;
            MOS();
        }
        else if(IR[0] == 'P' && IR[1] == 'D')       //PD
        {
            SI = 2;
            MOS();
        }
        else if(IR [0] == 'H')      //H
        {
            SI = 3;
            MOS();
            break;
        }
       else if(IR[0] == 'L' && IR[1] == 'R')       //LR
        {
            int i = IR[2]-48;  
            i = i*10 + ( IR[3]-48);

            // cout << "\n IR[2] " << IR[2] <<" IR[2]-48 "<< IR[2]-48 << " 1 - 48 "<< 1-48 ;
            // cout << " IR[3] "<<IR[3];
            // cout << " \n lr i" << i ;

            for(int j=0;j<=3;j++)
                R[j]=M[i][j];

            //for(int j=0;j<=3;j++)
              // cout<<R[j];

            cout<<endl;
        }
        else if(IR[0] == 'S' && IR[1] == 'R')       //SR
        {
            int i = IR[2]-48;
            i = i*10 +(IR[3]-48);
            //cout<<i;
            for(int j=0;j<=3;j++)
                M[i][j]=R[j];

            cout<<endl;
        }
        else if(IR[0] == 'C' && IR[1] == 'R')       //CR
        {
            int i = IR[2]-48;
            i = i*10 + (IR[3] - 48);
            //cout<<i;
            int count=0;

            for(int j=0;j<=3;j++)
                if(M[i][j] == R[j])
                    count++;

            if(count==4)
                C=true;

            //cout<<C;
        }
        else if(IR[0] == 'B' && IR[1] == 'T')       //BT
        {
            if(C == true)
            {
                int i = IR[2]-48;
                i = i*10 + (IR[3] - 48);

                IC = i;

            }
        }
    }
}




//Load Function
void OS::LOAD()
{


    cout<<"Reading Data..."<<endl;
    int x=0;
    do
    {
        for(int i=0;i<=40;i++)      //clear buffer
           buffer[i]='\0';

        infile.getline(buffer,44); 

        cout << " \n Printing Buffer:  ";
        for(int k=0;k<=40;k++)
           cout<<buffer[k];
        cout << "\n";
        if(buffer[0] == '$' && buffer[1] == 'A' && buffer[2] == 'M' && buffer[3] == 'J')
        {
            init();

        }
        else if(buffer[0] == '$' && buffer[1] == 'D' && buffer[2] == 'T' && buffer[3] == 'A')
        {
            IC = 00;
            Execute();

        }
        else if(buffer[0] == '$' && buffer[1] == 'E' && buffer[2] == 'N' && buffer[3] == 'D')
        {
            x=0;
            continue;
        }
        else
        {
            int k = 0;

            for(; x <100; ++x)
            {
                for(int j = 0 ; j<4; ++j)
                {

                    M[x][j] = buffer[k];
                    k++;
                }

                if(k == 40 || buffer[k] == ' ' || buffer[k] == '\n')
                {
                    // cout<<"Error"<<endl;
                    break;
                }

            }
            // x=10;

        }

    }while(!infile.eof()); 
    for(int i = 0; i<100; i++)
        {
            cout<<"M["<<i<<"]\t";
            for(int j = 0; j<4; j++ )
            {
                cout<<M[i][j];
            }
            cout<<endl;
        }
            //continues to take input till eof


}


int main()
{
    OS os;

    os.infile.open("input.txt", ios::in);
    os.outfile.open("output.txt", ios::out);

    if(!os.infile)
    {
        cout<<"Failure"<<endl;
    }
    else
    {
        cout<<"File Exist"<<endl;
    }

    os.LOAD();

    return 0;
}
