/*This is a digital clock. Also, user can give a color to the clock*/

#include <stdio.h>      //Including libraries
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

//There are main 8 symbols which are printed in the clock. The position of them in the console are defined here.(Here position is the offset to the symbol from left side)
#define P1 1    //First digit of hour
#define P2 8    //Second digit of hour
#define P3 14   //First colon
#define P4 20   //First digit of minute
#define P5 27   //Second digit of minute
#define P6 33   //Second colon
#define P7 39   //First digit of second
#define P8 46   //Second digit of second


int Help();                                             //Initializing the Help() function
int Invalid();                                          //Initializing the Invalid() function
int SayError(char arg[],int R);                         //Initializing the SayError() function
int Saytime();                                          //Initializing the Saytime() function
int PrintNumber(int,int);                               //Initializing the PrintNumber() function
int PrintDigit(int,int);                                //Initializing the PrintDigit() function
int PrintColon(int);                                    //Initializing the PrintColon() function
int Display(char arr[5][7],int position);               //Initializing the Display() function
int color1 = 1;                             //Creating two global integers to store the color and store the default color white
int color2 = 7;                             //For every color, there are particular two numbers



int main(int argc, char *argv[]){                                                   //Taking command line arguments
    typedef enum O_{O_Invalid1, O_Invalid2, O_Help, O_Saytime, O_Error}option;      //Creating a type named as option which can store 0-4 (4 options)
    option output = O_Saytime;                                                      //Creating an element of option data type and store the default value
    int argNo = 1;                                      //Creating an integer element to check command line argument by argument
    int errorArg,Since;                                 //Creating two integer variables to store the argNo of error input and since which letter, input is errorness

    while(argc > argNo){                                                               //If there are more arguments,
        if (argv[argNo][0]!='-'){                                                               //If it does not starts with '-',
            if(output==O_Invalid1){                                                             //If previous argument was '-c',
                if     (!strcasecmp(argv[argNo],"white"))    {color1=1; color2=7; output=O_Saytime;}    //If this argument is a name of a color,
                else if(!strcasecmp(argv[argNo],"black"))    {color1=0; color2=0; output=O_Saytime;}    //Set output to execute the clock
                else if(!strcasecmp(argv[argNo],"red"))      {color1=0; color2=1; output=O_Saytime;}    //Also, set the clock color by changing the value of two color variables
                else if(!strcasecmp(argv[argNo],"green"))    {color1=0; color2=2; output=O_Saytime;}
                else if(!strcasecmp(argv[argNo],"yellow"))   {color1=1; color2=3; output=O_Saytime;}    //Color values for different colors, (ansi codes)
                else if(!strcasecmp(argv[argNo],"blue"))     {color1=0; color2=4; output=O_Saytime;}    //white-1,7     black-0,7       red-0,1         green-0,2
                else if(!strcasecmp(argv[argNo],"magenta"))  {color1=1; color2=5; output=O_Saytime;}    //yellow-1,3      blue-0,4      magenta-1,5     cyan-0,6
                else if(!strcasecmp(argv[argNo],"cyan"))     {color1=0; color2=6; output=O_Saytime;}
                else   {output=O_Error;                                                         //If it is not a color name,
                        errorArg=argNo; Since=0;}                                               //Set output to send an error message and store the argNo as using Rewrite function
            }
        }else{                                                                         //If it starts with '-',
            if(argv[argNo][1]=='\0'){                                                           //If the argument is '-',
                if(output==O_Invalid1){                                                         //If the previous argument was '-c',
                    output=O_Error;                                                             //Set output to send an error message and store the argNo as the errorArg and 0 as Since;
                    errorArg=argNo; Since=0;
                }
            }else if(!strncmp(argv[argNo],"-h",2)){                                             //If the argument start with '-h',
                if(output==O_Invalid1){                                                         //If the previous argument was '-c',
                    output=O_Error;                                                             //Set output to send an error message and store the argNo as the errorArg and 0 as Since;
                    errorArg=argNo; Since=0;
                }else if(output==O_Error || output==O_Saytime){                                 //If output was set to send an error message to execute the clock
                    output=O_Help;                                                              //Set output to print a description
                }
            }else if(!strncmp(argv[argNo],"-c",2)){                                             //If the argument starts with '-c',
                if(argv[argNo][2]=='\0'){                                                       //If the argument is '-c',
                    if(output==O_Invalid1){                                                     //If the previous argument was '-c',
                        output=O_Error;                                                         //Set output to send an error message and store the argNo as the errorArg and 0 as Since;
                        errorArg=argNo; Since=0;
                    }else if(output==O_Error || output==O_Invalid2 || output==O_Saytime){       //If output was set to send an error message or to execute clock or the previous out was a wrong option(-***)
                        output=O_Invalid1;                                                      //Set output to send a Invalid input message (flagging this is '-c')
                    }
                }else{                                                                          //If the argument is -c***
                    if(output==O_Invalid1){                                                     //If the previous argument was '-c',
                        output=O_Error;                                                         //Set output to send an error message and store the argNo as the errorArg and 0 as Since;
                        errorArg=argNo; Since=0;
                    }else if(output==O_Error || output==O_Saytime){                             //If the output was set to send an error message or to execute the clock,
                        output=O_Error;                                                         //Set output to send an error message and store the argNo as the errorArg and 2 as Since;
                        errorArg=argNo; Since=2;
                    }
                }
            }else{                                                                              //If the argument is '-****'
                if(output==O_Invalid1){                                                         //If the previous argument was '-c',
                    output=O_Error;                                                             //Set output to send an error message and store the argNo as the errorArg and 0 as Since;
                    errorArg=argNo; Since=0;
                }else if(output==O_Error || output==O_Saytime){                                 //If the output was set to send an error message or to execute the clock,
                    output=O_Invalid2;                                                          //Set output to send an Invalid input message (flagging that this is '-****')
                }
            }
        }
        ++argNo;                                                                    //Jump to the next argument
    }

    if(output==O_Invalid1 || output==O_Invalid2){       //If output was set to send an Invalid input message,
        Invalid();                                      //Send it using Invalid() function
    }else if(output==O_Help){                           //If output was set to print description,
        Help();                                         //Print it using Help() function
    }else if(output==O_Saytime){                        //If output was set to execute the clock,
        Saytime();                                      //Execute the clock using Saytime() function
    }else{                                              //Otherwise(if output was set to send an error message)
        SayError(argv[errorArg],Since);                 //Send it using SayError() function (Current wrong input is sent as an argument)
    }

    return 0;
}



int Saytime(){                                          //This function checks the current time and date second by second and print it
        int year,month,day,hour,minute,second;          //Creating 6 integer variables to store the time
        time_t nowTime;                                 //Creating a time_t type variable to store calender time
        struct tm * Timeinfo;                           //Creating the structure to hold the time and date

        printf("\x1b[2J");                              //Clears the console
        for (int i=0;1;i++){                            //creating a infinite loop
                time (&nowTime);                        //Take the system time
                Timeinfo = localtime (&nowTime);        //Put the time into the structure

                hour      = Timeinfo->tm_hour;          //Take the hours
                minute    = Timeinfo->tm_min;           //Take the minutes
                second    = Timeinfo->tm_sec;           //Take the seconds
                day       = Timeinfo->tm_mday;          //Take the day
                month     = (Timeinfo->tm_mon)+1;       //Take the month (0-11)+1 -> (1-12)
                year      = (Timeinfo->tm_year)+1900;   //Take the year (Here number of years is counted since 1900)

                printf("\x1b[1;1f");                    //Move the cursor to the top left corner of the console
                PrintNumber(hour,P1);                   //Print the number of hours(two digits) using PrintNumber() function at the P1 position
                PrintColon(P3);                         //Print the first colon using PrintColon() function at the P3 position
                PrintNumber(minute,P4);                 //Print the number of minutes(two digits) using PrintNumber() function at the P4 position
                PrintColon(P6);                         //Print the first colon using PrintColon() function at the P6 position
                PrintNumber(second,P7);                 //Print the number of seconds(two digits) using PrintNumber() function at the P7 position
                //Here font color is changed, prints the day ,month, year and font color again changed to white
                printf("\e[%d;3%dm\n\n\n\n\n\n\n\x1b[22C%04d-%02d-%02d\e[1;37m\n",color1,color2,year,month,day);
                sleep(1);                               //Sleep for 1 second
        }

        return 0;
}



int SayError(char arg[],int since){                    //This function prints the error message mentioning the error input. Error input is taken as an argument to this function

    for(int i=since;arg[i]!='\0';i++){                 //Print the error input
        printf("%c",isupper(arg[i])?arg[i]+32:arg[i]); //in lower case letters
    }
                                                       //Print the error message
    printf(" :This is not a valid color, Please enter one of these colours: black, red, green, yellow, blue, magenta, cyan, white\n");

    return 0;
}



int Help(){                                  //This function prints a description about the program
                                             //Prints the description
    printf("usage : clock -h                quick help on cmd\nusage : clock -c <color>        print clock with a color\n<color-black|red|green|yellow|blue|magenta|cyan|white>  supported colors\n");

    return 0;
}



int Invalid(){                               //This function mentions the invalid argument error
                                             //Prints the error
    printf("\e[0;31mInvalid\e[1;37m use of arguments.\nusage : clock \e[1;34m-h\e[1;37m                quick help on cmd\nusage : clock \e[1;34m-c\e[1;37m <color>        print clock with a color\n");

    return 0;
}



int PrintNumber(int number,int position){   //This function divides the numbers of hours/minutes/seconds to two digits and print them separately
    int P_1st, P_2nd;                       //Creating two integer variables to store positions of two digits

    int firstdigit = number/10;             //Calculating the first digit
    int seconddigit = number%10;            //Calculating the second digit

    if      (position==P1){P_1st = P1;      //Assigning the positions of two digits
                           P_2nd = P2;}
    else if (position==P4){P_1st = P4;
                           P_2nd = P5;}
    else if (position==P7){P_1st = P7;
                           P_2nd = P8;}

    PrintDigit(firstdigit,P_1st);           //Printing the first digit using PrintDigit function
    PrintDigit(seconddigit,P_2nd);          //Printing the second digit using PrintDigit function

    return 0;
}



int PrintDigit(int digit,int position){                 //This function prints digit
    //Here for each digit there is a array(5*7 including a additional '\0' column). '1's are there where background color should be added
    char arr0[5][7] = {{1,1,1,1,1,1,0},                 //digit '0'
                      {1,1,0,0,1,1,0},
                      {1,1,0,0,1,1,0},
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};
    char arr1[5][7] = {{0,0,0,0,1,1,0},                 //digit '1'
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0}};
    char arr2[5][7] = {{1,1,1,1,1,1,0},                 //digit '2'
                      {0,0,0,0,1,1,0},
                      {1,1,1,1,1,1,0},
                      {1,1,0,0,0,0,0},
                      {1,1,1,1,1,1,0}};
    char arr3[5][7] = {{1,1,1,1,1,1,0},                 //digit '3'
                      {0,0,0,0,1,1,0},
                      {1,1,1,1,1,1,0},
                      {0,0,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};
    char arr4[5][7] = {{1,1,0,0,1,1,0},                 //digit '4'
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0},
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0}};
    char arr5[5][7] = {{1,1,1,1,1,1,0},                 //digit '5'
                      {1,1,0,0,0,0,0},
                      {1,1,1,1,1,1,0},
                      {0,0,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};
    char arr6[5][7] = {{1,1,1,1,1,1,0},                 //digit '6'
                      {1,1,0,0,0,0,0},
                      {1,1,1,1,1,1,0},
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};
    char arr7[5][7] = {{1,1,1,1,1,1,0},                 //digit '7'
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0},
                      {0,0,0,0,1,1,0}};
    char arr8[5][7] = {{1,1,1,1,1,1,0},                 //digit '8'
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0},
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};
    char arr9[5][7] = {{1,1,1,1,1,1,0},                 //digit '9'
                      {1,1,0,0,1,1,0},
                      {1,1,1,1,1,1,0},
                      {0,0,0,0,1,1,0},
                      {1,1,1,1,1,1,0}};

    if      (digit==0){Display(arr0,position);}         //If the digit is '0', printing it using Display() function
    else if (digit==1){Display(arr1,position);}         //If the digit is '1', printing it using Display() function
    else if (digit==2){Display(arr2,position);}         //If the digit is '2', printing it using Display() function
    else if (digit==3){Display(arr3,position);}         //If the digit is '3', printing it using Display() function
    else if (digit==4){Display(arr4,position);}         //If the digit is '4', printing it using Display() function
    else if (digit==5){Display(arr5,position);}         //If the digit is '5', printing it using Display() function
    else if (digit==6){Display(arr6,position);}         //If the digit is '6', printing it using Display() function
    else if (digit==7){Display(arr7,position);}         //If the digit is '7', printing it using Display() function
    else if (digit==8){Display(arr8,position);}         //If the digit is '8', printing it using Display() function
    else              {Display(arr9,position);}         //If the digit is '9', printing it using Display() function

    return 0;
}



int PrintColon(int position){                       //This function prints the colon (:)
    //As same as above digits
    char arrColon[5][7] = {{0,0,0,0,0,0,0},         //Colon ':'
                           {0,0,1,1,0,0,0},
                           {0,0,0,0,0,0,0},
                           {0,0,1,1,0,0,0},
                           {0,0,0,0,0,0,0}};

    Display(arrColon,position);                     //Printing the colon using Display() function

    return 0;
}



int Display(char arr[5][7],int position){                       //This function prints digits and colon at given position
    for(int i=0;i<5;i++){                                       //Print row by row
        printf("\n\x1b[%dC",position);                          //Move cursor to the position of the below line

        for(int j=0;j<6;j++){                                   //Column by column in the particular row,
            if(arr[i][j]){                                      //Finding whether it is a '1' or '0' and if it is a '1',
                printf("\e[%d;4%dm \e[0;40m",color1,color2);    //Print a space with needed background color and change it color again to black
            }else{                                              //If it is a '0',
                printf("\e[%d;3%dm \e[1;37m",color1,color2);    //Print a space with needed font color and change it color again to white
            }
        }
    }

    printf("\n\x1b[%dA",6);                                     //Bring cursor back to the top left corner of the console

    return 0;
}


