#include <cstring>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int roleChosen = 0;

//case 1
int paperAmount = 5;
int* pntPaperAmount = &paperAmount;
int developerAmount = 5;
int* pntDeveloperAmount = &developerAmount;
int inkAmount = 5;
int* pntInkAmount = &inkAmount; //   <--------------
//teha sama pointeri värk nendele alumistele väärtustele ka :) TODO
int paperSpent = 0;         
int developerSpent = 0;
int inkSpent = 0;

int photosToPrint = 5;
int photosToDevelop = 5;
int photosPrinted = 0;
int photosDeveloped = 0;
//teha sama pointeri värk nendele ylemistele väärtustele ka :)
double totalRevenue = 0;

bool exitChosen = false;
bool fullExitChosen = false;

int photographerChoice = 0;
int receptionistChoice = 0;
int customerChoice = 0;

int currentClient;

struct client
{
    bool isOccupied; //checks if index number in use
    bool rushOrder;
    int rushOrderInt;
    char name[20];
    int day, month, year;
    int photosToPrint, photosToDevelop, photosPrinted, photosDeveloped;
    bool isNew = false;
    bool isForwarded = false;
    bool isCompleted = false;
};




client clients[10]; //allows max of 10 clients

int userChoice(int Choice)
{
    //system("cls"); //clears the terminal after each input, only works in windows machines, (for some reason my vs code terminal bugs out if this is included but works in the .exe, uncomment before finishing project)
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
        printf_s("1. View new orders\n2. View ongoing orders\n3. View completed orders\n4. View today's revenue\n5. View today's spent materials\n6. Exit\n");

        scanf_s("%d", &receptionistChoice);

        switch (userChoice(receptionistChoice))
        {
        case 1:
            while (!exitChosen) {
                printf_s("Viewing new orders\n--------------\n");
                for (int i = 0; i < 10; i++)
                {
                    if (clients[i].isNew){
                        printf_s("%s has made an order!\nWould you like to forward the order to the photographer?\n 1. Yes\n 2. No\n", clients[i].name);

                        scanf_s("%d", &receptionistChoice);
                        if (receptionistChoice == 1)
                        {
                            clients[i].isNew = false;
                            clients[i].isForwarded = true;
                        }
                    }
                    else {printf_s("No ongoing orders found\n");}
                }
                break;
                
            }
            break;

        case 2:
            printf_s("Viewing ongoing orders\n--------------\n");
            for (int i = 0; i < 10; i++)
            {
                if (clients[i].isForwarded)
                {
                    printf_s("\n Customer id: %d\n Customer name: %s\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline:\n %d/%d/%d\n\n", i, clients[i].name, clients[i].photosToPrint, clients[i].photosToDevelop, clients[i].photosPrinted, clients[i].photosDeveloped, clients[i].day, clients[i].month, clients[i].year);
                }
                else break;
            }
            break;
            

        case 3:
            printf_s("Viewing completed orders\n---------------\n");
            for (int i = 0; i < 10; i++)
            {
                if (clients[i].isCompleted){
                    printf_s("Order for %s is completed!\n", clients[i].name);
                break;
                }
            }
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


void customer() //Function for the customer role  // tbh tundub semi done, kui keegi viitsib ss võib selle switchiks teha TODO
{
    printf_s("Customer chosen\n");


    printf_s("What would you like to do?\n 1. Print and/or develop photos\n 2. View order status\n 3. Exit\n");
    
    scanf_s("%d", &customerChoice);
    if (customerChoice == 3) return; //Exits customer view

    else if (customerChoice == 1) //Creates a new customer and starts to log his/her order
        while (!exitChosen)
        {
            for (int i = 0; i < 10; i++)
            {
                if (!clients[i].isOccupied)
                {
                    currentClient = i;
                    clients[currentClient].isOccupied = true;
                    clients[currentClient].isNew = true;
                    printf_s("Your client number is %d, Dont forget it!\n", i);
                    break;
                }
            }




            printf_s("Input your name:\n");
            scanf_s(" %[^\n]", clients[currentClient].name, (unsigned)sizeof(clients[currentClient].name));
            
            printf_s("%s.\n", clients[currentClient].name);

            printf_s("How many photos would you like to print?\n");

            scanf_s("%d", &clients[currentClient].photosToPrint);

            printf_s("How many photos would you like to develop?\n");

            scanf_s("%d", &clients[currentClient].photosToDevelop);

            printf_s("When would you like to collect the photos? (dd mm yyyy)\n");

            scanf_s("%d %d %d", &clients[currentClient].day, &clients[currentClient].month, &clients[currentClient].year);
            
            printf_s("Would you like a rush order or regular order?\n 0. Regular\n 1. Rush\n");

            scanf_s("%d", &clients[currentClient].rushOrderInt);
            
            switch (clients[currentClient].rushOrderInt)
            {
            case 0:
                printf_s("Regular order selected\n");
                clients[currentClient].rushOrder = false;
                exitChosen = true;
                break;
            case 1:
                printf_s("Rush order selected\n");
                clients[currentClient].rushOrder = true;
                exitChosen = true;
                break;
            default:
                printf_s("Invalid choice\n");
            }
        }
    else if (customerChoice == 2) //allows the customer to see progress on his/her order
    {
        printf_s("Enter your Customer ID\n");
        scanf_s("%d", &currentClient);
        printf_s("Current progress:\n %d Photos to print\n %d Photos to develop\n %d Photos printed\n %d Photos developed\n Deadline: %d/%d/%d", clients[currentClient].photosToPrint, clients[currentClient].photosToDevelop, clients[currentClient].photosPrinted, clients[currentClient].photosDeveloped, clients[currentClient].day, clients[currentClient].month, clients[currentClient].year);
    }
}

void photographer() // the photographer, the most developed right now, but still not finished. the photographer can complete the orders by using the necessary materials.
{
    int photographerCustomerChoice = 0;
    client currentClient;
    printf_s("Photographer chosen\n");
    printf_s("You currently have: %d paper, %d developer and %d ink\n", paperAmount, developerAmount, inkAmount);
    printf_s("Orders to complete:\n\n");
    for (int i = 0; i < 10; i++)
    {
        if (clients[i].isForwarded){
            printf_s("Customer %d has an uncomplete order!\n", i);
        }
        else break;
    }

    printf_s("Select your customer. (Enter only number)\n");

    scanf_s("%d", &photographerCustomerChoice);
    currentClient = clients[photographerCustomerChoice];
    
    while (!exitChosen)
    {
        printf_s("You have %d photos printed and %d photos developed\n", photosPrinted, photosDeveloped);
        printf_s("You have %d photos to print and %d photos to develop.\n\n", photosToPrint, photosToDevelop);
        printf_s("What would you like to do? (Enter only number)\n");
        printf_s("1. Develop photos\n2. Print photos\n3. Finish order.\n4. Exit\n");
    
        scanf_s("%d", &photographerChoice);
    
        switch (userChoice(photographerChoice))
        {
            case 1: // lisa if checki mis annab erineva lause kui sul on materjalid otsas.
            if (paperAmount == 0 || developerAmount == 0) // currently the only system implemented. on inputting '1', the paper and developer amount goes down and the photosDeveloped variable goes up.
            { //case 1
                printf_s("Insufficient materials!\n");
                continue;
            }
                //TODO add if to check if you need to develop more photos for the client
                printf_s("Developing photos.\n");
                --currentClient.photosToDevelop;
                (*pntDeveloperAmount)--;
                (*pntPaperAmount)--;
                ++currentClient.photosDeveloped;
                ++developerSpent;
                ++paperSpent;
                totalRevenue += 1.2f;
                break;
            case 2:

                
                //TODO add if to check if you need to print more photos for the client            
                printf_s("Printing photos.\n");
                --currentClient.photosToPrint;
                (*pntInkAmount)--;
                ++currentClient.photosPrinted;
                ++inkSpent;
                totalRevenue += 1.2f;
                break;
            case 3:
                if (currentClient.photosToPrint == 0 && currentClient.photosToDevelop == 0) {
                    currentClient.isCompleted = true;
                    currentClient.isForwarded = false;
                    printf_s("Order Completed!\n");
                }
                else {
                    printf_s("Cannot complete order! Order still has photos to print/develop\n");
                }
                exitChosen = true;
                break;

            case 4:
                exitChosen = true;
                break;

            default:
                printf_s("Invalid choice\n");
                break;
        }
        clients[photographerCustomerChoice] = currentClient;
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

