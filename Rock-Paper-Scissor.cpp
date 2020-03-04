#include<iostream>
#include<stdlib.h>
#include<thread>
using namespace std;
//using namespace this_thread;

char OppositeOf(char d);
string getName(char d);

class count
{
    public:
        int Rock,Paper,Scissor;
        
        count()
        {
        	Rock=0;
        	Paper=0;
        	Scissor=0;
		}

        void incr(char c)
        {
            switch(c)
            {
                case 'r':Rock++;
                        break;
                case 'p':Paper++;
                        break;
                case 's':Scissor++;
                        break;
            }
        }

        char getMax()
        {
        //rock==scissor:'T'   rock==Paper:'Q'  Paper==Scissor:'O'  rock==Paper==Scissor:'E'
            char ret;
            if(Rock == Paper && Paper == Scissor) //all equal
            {                
                ret='E';
            }
            else if(Rock > Paper && Rock > Scissor)
                ret='r';
            else if(Paper > Rock && Paper > Scissor)
                ret='p';
            else if(Scissor > Rock && Scissor > Paper)
                ret='s';
            else if(Rock == Paper)
                ret='Q';
            else if(Rock == Scissor)
                ret='T';
            else if(Paper == Scissor)
                ret='O';
            return ret;
            
            
        }
        void print()
        {cout<<"\nr:"<<Rock<<" p:"<<Paper<<" s:"<<Scissor;}
};

class CPU
{
    count PlrDrw,rockNext,paperNext,scissorNext;
    int rockRange,paperRange,scissorRange;
    int rndm;
    bool dir;
    int fav_Rising_COUNT;
    char fav_Rising;
    
    
    void incRange(char d)
    {
        switch(d)
        {
            case 'r':if(rockRange == paperRange-1)
                        if(paperRange < scissorRange-1)
                            paperRange++;
                    if(rockRange < paperRange-1)
                        rockRange++;             
                    // else if(rockRange == paperRange)
                    // {
                    //     if(paperRange<scissorRange)
                    //     {
                    //         rockRange++;
                    //         paperRange++;
                    //     }                        
                    // }
                    //cout<<"\nR inc"        ;

                    break;

            case 'p':if(dir)
                     {
                        if(paperRange < scissorRange-1)
                            paperRange++;
                        dir=false;
                     }
                     else if(!dir)
                     {
                        if(rockRange > 1)
                            rockRange--;
                        dir=true;
                     }
            
                    // if(rockRange>=1)
                    //     rockRange--;
                    // if(paperRange<9)
                    //     paperRange++;
                    break;

            case 's':if(paperRange == rockRange+1)
                        if(rockRange > 1)
                            rockRange--;
                    if(paperRange > rockRange+1)
                        paperRange--;
                    break;
        }
    }

    public: 
        char inp,plr_prvINP;
        
        CPU()
	    {
	    	rockRange=3;
			paperRange=6;
			scissorRange=9;
			dir=true;
			plr_prvINP=' ';
            fav_Rising_COUNT=0;
            fav_Rising=' ';
		}

        void draw()
        {
            rndm=rand() % 9 + 1;
            char nxtPreDtn,plrHBBT;
            
            plrHBBT=PlrDrw.getMax();
            //PlrDrw.print();
            
            switch (plr_prvINP)
            {
                case 'r':nxtPreDtn=rockNext.getMax();
                        break;
                case 'p':nxtPreDtn=paperNext.getMax();
                        break;
                case 's':nxtPreDtn=scissorNext.getMax();
                        break;
            }
            // cout<<"\n\nHabbit:"<<plrHBBT<<"\tNXT: "<<nxtPreDtn<<"\tPrev: "<<plr_prvINP;
            // cout<<"\n\nRockNExt: ";rockNext.print();
            // cout<<"\nPaperNEXT: ";paperNext.print();
            // cout<<"\nScissorNext: ";scissorNext.print();

            if(plrHBBT==nxtPreDtn)//player habbit meets next draw prediction
            {
                switch (plrHBBT)
                {
                    case 'r':
                             if(fav_Rising == 's')
                             {
                              //   cout<<"tactical doge";
                                 incRange('r');
                                 incRange('r');
                             }
                             else
                             {                             
                                incRange('p');
                                incRange('p');    
                             }                             
                             incRange('p');
                            break;

                    case 'p':if(fav_Rising == 'r')
                             {
                               //  cout<<"tactical doge";
                                 incRange('p');
                                 incRange('p');
                             }
                             else
                             {                             
                                incRange('s');
                                incRange('s');    
                             }       
                             incRange('s');
                            break;

                    case 's':if(fav_Rising == 'p')
                             {
                               //  cout<<"tactical doge";
                                 incRange('s');
                                 incRange('s');
                             }
                             else
                             {                             
                                incRange('r');
                                incRange('r');    
                             }       
                             incRange('r');
                            break;
                    case 'T'://player might draw rock or scissor. So there is no chance of winning. So CPU draws rock to make tie
                             incRange('r');
                             incRange('r');
                             incRange('r');
                            break;
                    case 'Q'://player might draw rock or paper. So to win or make tie, CPU draws paper
                             incRange('p');
                             incRange('p');
                             incRange('p');
                            break;
                    case 'O'://player might draw paper or scissor.So to win or make tie, CPU draws scissor
                             incRange('s');
                             incRange('s');
                             incRange('s');
                            break;
                    case 'E'://player might draw rock, paper or scissor.So CPU dont know what to do.
                             //  ;cout<<"\n\n()()(prev:): ";
                               
                            break;
                
                }
            }
            else
            {
                if(plrHBBT=='r')
                {
                    if(!(fav_Rising == ' '))
                    {
                      //  cout<<"fav rising";
                        incRange(OppositeOf(fav_Rising));
                        incRange(OppositeOf(fav_Rising));
                    }

                    switch(rockNext.getMax())
                    {
                        case 'r':if(fav_Rising == 's')
                                 {
                                     
                                     incRange('r');
                                 }
                                 else
                                 {
                                    incRange('p');
                                 }                                 
                                break;                        
                        case 'p':incRange('s');
                                break;                        
                        case 's':incRange('r');
                                break;                        
                        case 'T':incRange('r');
                                break;                        
                        case 'Q':incRange('p');
                                break;                        
                        case 'O':incRange('s');
                                break;                        
                        case 'E':incRange('p');
                                break;
                    }
                }
                else if(plrHBBT=='p')
                {
                    if(!(fav_Rising == ' '))
                    {
                       // cout<<"fav rising";
                        incRange(OppositeOf(fav_Rising));
                        incRange(OppositeOf(fav_Rising));
                    }

                    switch(paperNext.getMax())
                    {
                        case 'r':incRange('p');
                                break;                        
                        case 'p':if(fav_Rising == 'r')
                                 {                                     
                                     incRange('p');
                                 }
                                 else
                                 {
                                    incRange('s');
                                 }
                                    
                                break;                        
                        case 's':incRange('r');
                                break;                        
                        case 'T':incRange('r');
                                break;                        
                        case 'Q':incRange('p');
                                break;                        
                        case 'O':incRange('s');
                                break;                        
                        case 'E':incRange('r');
                                break;
                    }
                }
                else if(plrHBBT=='s')
                {
                    if(!(fav_Rising == ' '))
                    {
                      //  cout<<"fav rising";
                        incRange(OppositeOf(fav_Rising));
                        incRange(OppositeOf(fav_Rising));
                    }

                    switch(scissorNext.getMax())
                    {
                        case 'r':incRange('p');
                                break;                        
                        case 'p':incRange('s');
                                break;                        
                        case 's':if(fav_Rising == 'p')
                                 {
                                    
                                    incRange('s');
                                 }
                                 else
                                 {
                                    incRange('r');      
                                 }
                                 
                                 
                                break;                        
                        case 'T':incRange('r');
                                break;                        
                        case 'Q':incRange('p');
                                break;                        
                        case 'O':incRange('r');
                                break;                        
                        case 'E':incRange('r');
                                break;
                    }
                }
                else if(plrHBBT=='T')
                {
                    if(nxtPreDtn=='r')
                    {
                        incRange('p');
                    }
                    else if(nxtPreDtn=='s')
                    {
                        incRange('r');
                    }
                    else
                        incRange('p');
                }
                else if(plrHBBT=='Q')
                {
                    if(nxtPreDtn=='r')
                    {
                        incRange('p');
                    }
                    else if(nxtPreDtn=='p')
                    {
                        incRange('s');
                    }
                    else
                        incRange('r');
                }
                else if(plrHBBT=='O')
                {
                    if(nxtPreDtn=='p')
                    {
                        incRange('s');
                    }
                    else if(nxtPreDtn=='s')
                    {
                        incRange('r');
                    }
                    else
                        incRange('p');
                }
                else if(plrHBBT=='E')
                {
                 //   cout<<"[here0]\nprev:"<<plr_prvINP<<" nxt:"<<nxtPreDtn;

                    if(plr_prvINP==' ')
                    {
                    //    cout<<"[here1]";
                        //first time
                    }
                    else
                    {
                      //  cout<<"\n\nwill draw:"<<OppositeOf(nxtPreDtn);
                        
                        incRange(OppositeOf(nxtPreDtn));
                        incRange(OppositeOf(nxtPreDtn));
                        incRange(OppositeOf(nxtPreDtn));
                        incRange(OppositeOf(nxtPreDtn));     
                        
                    }
                    
                }
            }
            
          //  cout<<"\n\nRANGE:\tR->"<<rockRange<<"<-P->"<<paperRange<<"<-S->"<<scissorRange<<"\nfav rising:"<<fav_Rising<<" :("<<fav_Rising_COUNT<<")\n\n";
            if(rndm<=rockRange)
            {
                inp='r';
            }
            else if(rndm<=paperRange)
            {
                 inp='p';
            }   
            else if(rndm<=scissorRange)
            {
                 inp='s';
            }
        }
        void see(char plr_curInp)
        {
            PlrDrw.incr(plr_curInp);
            switch (plr_prvINP)
            {
                case 'r':rockNext.incr(plr_curInp);
                        break;
                case 'p':paperNext.incr(plr_curInp);
                        break;
                case 's':scissorNext.incr(plr_curInp);
                        break;                
            }

            if(plr_curInp==plr_prvINP)
            {
                fav_Rising_COUNT++;
                if(fav_Rising_COUNT >= 2)
                    fav_Rising=plr_curInp;
            }
            else
                fav_Rising_COUNT=0;
            

            plr_prvINP=plr_curInp;

            /*
            cout<<"\n\nPLR:";
            PlrDrw.print();
            cout<<"\nrck:";
            rockNext.print();
            cout<<"\nppr:";
            paperNext.print();
            cout<<"\nscr:";
            scissorNext.print();
            */
        }

};

int main()
{
    
    bool run=true;    
    CPU cpu;
    char ch;
    int p_score=0,c_score=0;
    char inp;
    while(run)
    {
        if(system("cls")!=0)
            system("clear");
        cout<<"Rock:r\tPaper:p\tScissor:s\t\t\tQuit:q\n\n";                
        cout<<"Player:"<<p_score<<"\t\tCPU:"<<c_score<<"\n\nDARW:";
        cpu.draw();
        cin>>inp;
        if(inp=='q')
            run=false;        
        else
        {
            if(!(inp== 'r' || inp=='p' || inp=='s'))
                cout<<"\n[WRONG DRAW (retry)]";
            else
            {
                cout<<"\nPlayer\t\t\tCPU\n------\t\t\t---\n"<<getName(inp)<<"\t\t\t"<<getName(cpu.inp);           
                if(inp==OppositeOf(cpu.inp))
                    p_score++;
                else if(cpu.inp==OppositeOf(inp))
                    c_score++;    
            }                   

            cpu.see(inp);             
			cout<<"\n\n[press enter to continue]"          ;
            cin.get();cin.get();       
        }
        
    }
    return 0;
}

string getName(char d)
{
    string ret;
    switch(d)
    {
        case 'r': ret="Rock";
                break;
        case 'p': ret="Paper";
                break;
        case 's': ret="Scissor";
                break;
    }
    return ret;
}

char OppositeOf(char d)
{
    char ret;
    if(d=='r')
        ret='p';
    else if(d=='p')
        ret='s';
    else //if(d=='s')
        ret='r';
    
    return ret;
}


