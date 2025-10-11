
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int roleChosen = 0;

//case 1
int paperAmount = 5;
int developerAmount = 5;
int inkAmount = 5;

int paperSpent = 0;
int developerSpent = 0;
int inkSpent = 0;

int photosToPrint = 5;
int photosToDevelop = 5;
int photosPrinted = 0;
int photosDeveloped = 0;

double totalRevenue = 0;

bool exitChosen = false;
bool fullExitChosen = false;

int photographerChoice = 0;
int receptionistChoice = 0;

int userChoice(int Choice)
{
    system("cls"); //clears the terminal after each input, only works in windows machines, (for some reason my vs code terminal bugs out if this is included but works in the .exe, uncomment before finishing project)
    if(Choice == 9)
    {
        exitChosen = true;
        return 0;
    }
    else
    {
        return Choice;
    }
}


void receptionist() // heavily in development, the receptionist, currently the user can view the temporary text that is implemented. the receptionist will be able to see the orders that the customer has placed.
{
    printf_s("Receptionist chosen\n");
    while (!exitChosen) {


        printf_s("What would you like to do? (Enter only number)\n");
        printf_s("1. View pending orders\n2. View ongoing orders\n3. View completed orders\n4. View today's revenue\n5. View today's spent materials\n6. Exit\n");

        scanf_s("%d", &receptionistChoice);

        switch (userChoice(receptionistChoice)) // since currently we do not have an order making system i can not create a system to arrange the orders - virgo
        {
        case 1:
            printf_s("Viewing pending orders\n--------------\n");
            break;

        case 2:
            printf_s("Viewing ongoing orders\n--------------\n");
            break;

        case 3:
            printf_s("Viewing completed orders\n---------------\n");
            break;

        case 4:
            printf_s("Viewing today's revenue\n--------------\n");
            printf_s("Today's revenue = %.2lf\n", totalRevenue);
            break;

        case 5:
            printf_s("Viewing today's spent materials\n---------------\n");
            printf_s("Ink spent = %d\nPaper spent = %d\nDeveloper spent = %d\n", inkSpent, paperSpent, developerSpent);
            break;

        case 6:
            exitChosen = true;
            break;

        default:
            printf_s("Invalid choice\n");
            break;
        }
    }
}

void customer() // heavily in development, the customer will be the one who can make an order and decide if it's a rush order or not.
{
    printf_s("Customer chosen\n");

    printf_s("What would you like to do? (Enter only number)\n");
    printf_s("1. Develop photos\n2. Print photos\n3. Exit\n4. Submit a report. (IN DEVELOPMENT)\n");
}

void photographer() // the photographer, the most developed right now, but still not finished. the photographer can complete the orders by using the necessary materials.
{
    printf_s("Photographer chosen\n");
    printf_s("You currently have: %d paper, %d developer and %d ink\n", paperAmount, developerAmount, inkAmount);
    
    while (!exitChosen)
    {
        printf_s("You have %d photos printed and %d photos developed\n", photosPrinted, photosDeveloped);
        printf_s("You have %d photos to print and %d photos to develop.\n\n", photosToPrint, photosToDevelop);
        printf_s("What would you like to do? (Enter only number)\n");
        printf_s("1. Develop photos\n2. Print photos\n3. Exit\n4. Submit a report. (IN DEVELOPMENT)\n");
    
        scanf_s("%d", &photographerChoice);
    
        switch (userChoice(photographerChoice))
        {
            case 1: // lisa if checki mis annab erineva lause kui sul on materjalid otsas.
            if (paperAmount == 0 || developerAmount == 0) // currently the only system implemented. on inputting '1', the paper and developer amount goes down and the photosDeveloped variable goes up.
            { //case 1
                printf_s("Insufficient materials!\n");
                continue;
            }
            
                printf_s("Developing photos.\n");
                --photosToDevelop;
                --developerAmount;
                --paperAmount;
                ++photosDeveloped;
                ++developerSpent;
                ++paperSpent;
                totalRevenue += 1.2f;
                break;
            case 2:
                break;
            case 3:
                exitChosen = true;
                break;
            default:
                printf_s("Invalid choice\n");
                break;
        }
    }
}
int main()
{


    while(!fullExitChosen) //this is the main menu loop that allows the user to go back and forth between different roles
    {
        exitChosen = false; //used to make sure that the user can properly back out of a role (e.g photographer -> menu -> receptionist).
        
        printf_s("Choose your role: (Enter only number)\n"); // currently there's a bug where the system goes crazy if a user inputs a character instead of a number. planning to fix.
        printf_s("1. Receptionist (IN DEVELOPMENT)\n2. Customer (IN DEVELOPMENT)\n3. Photographer\n4. Quit Program\n"); // the choice can be made by inputting a number

        scanf_s("%d", &roleChosen); //user makes a choice using this function.
    
        switch (userChoice(roleChosen)) // this switch holds the necessary code for everything regarding different roles and their respective systems.
        {
        case 1: 
            receptionist();
            break;

        case 2:
            customer();
            break;
        case 3: 
            photographer();
            break;
        
            case 4: // allows the user to quit the program by not closing the program by hand.
            printf_s("Quitting program\n");
            fullExitChosen = true;
            break;
        
        default:
            printf_s("Invalid choice\n");
            break;
        }
    }
    
    
    return 0;
}

