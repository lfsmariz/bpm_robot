#include <iostream>
#include <fstream>
#include <string>

struct canvas
{
    int axis_x;
    int axis_y;
    char *canv;
};

struct arm_bot
{   
    int pos_x = 0, pos_y = 0;
    int command;
    short int ink = 0;
};


void empty_canvas(char tmpcanv[], int tmp_size)
{
    
    for (int i = 0; i < tmp_size; i++)
    {
        tmpcanv[i] = '0';
    }
}


int main()
{
    std::ifstream infile;
    infile.open("name.txt");

    if (infile.fail())
    {
        std::cerr << "Error opening archive \n";
        exit(1);
    }

    canvas sample;
    arm_bot irobot;
    int tmp_size;

    infile >> sample.axis_x >> sample.axis_y;
    infile >> irobot.command;
    tmp_size = sample.axis_x * sample.axis_y;

    sample.canv = new char[tmp_size];
    
    empty_canvas(sample.canv, tmp_size);


    int count = 0, move = 0;
    char tmp_act;


    while(count < irobot.command)
    {
        infile >> tmp_act;

        switch (tmp_act)
        {
        case 'a':
            irobot.ink = 1;
            break;
        
        case 's':
            irobot.ink = 0;
            break;
        

        case 'c':
            infile >> move;
            if (irobot.ink == 1)
            {
                for (int i = 0; i < move ; i++)
                {   
                    sample.canv[irobot.pos_y * sample.axis_x + irobot.pos_x] = '1';
                    irobot.pos_y--;  
                }
                break;
            }

            else
            {
                for (int i = 0; i < move ; i++)
                {   
                    irobot.pos_y--;  
                }
                break;
            }

        case 'b':
            infile >> move;
            if (irobot.ink == 1)
            {
                for (int i = 0; i < move ; i++)
                {   
                    sample.canv[irobot.pos_y * sample.axis_x + irobot.pos_x] = '1';
                    irobot.pos_y++; 
                }
                break;
            }

            else
            {
                for (int i = 0; i < move ; i++)
                {    
                    irobot.pos_y++;  
                }
                break;
            }
            

        case 'e':
            infile >> move;
            if (irobot.ink == 1)
            {
                for (int i = 0; i < move ; i++)
                {   
                    sample.canv[irobot.pos_y * sample.axis_x + irobot.pos_x] = '1';
                    irobot.pos_x--;  
                }
                break;
            }

            else
            {
                for (int i = 0; i < move ; i++)
                {   
                    irobot.pos_x--;  
                }
                break;
            }

        case 'd':
            infile >> move;
            if (irobot.ink == 1)
            {
                for (int i = 0; i < move ; i++)
                {   
                    sample.canv[irobot.pos_y * sample.axis_x + irobot.pos_x] = '1';
                    irobot.pos_x++;  
                }
                break;
            }

            else
            {
                for (int i = 0; i < move ; i++)
                {   
                    irobot.pos_x++;  
                }
                break;
            }
        }
        count++;
    }    


    std::ofstream out_bpm ("name.bpm", std::ofstream::out);

    out_bpm << "P1 \n";
    out_bpm << "#LuizFilipe \n";
    out_bpm << sample.axis_x << " " << sample.axis_y << " ";

    for (int i = 0; i < tmp_size; i++)
    {
        out_bpm << sample.canv[i];
        out_bpm << " ";
    }
    

    out_bpm.close();

    delete sample.canv;

    return 0;
}