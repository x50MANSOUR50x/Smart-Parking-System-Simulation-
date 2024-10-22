#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include "park.h"

unsigned char track_spaces(void);
unsigned char calculate_fee(int *parking_duration);
void search_car(unsigned char id);
void display_status(void);
void reverse_entries(void);

// Because the car is a global struct, the struct's members are initialized with 0.
struct Car
{
    int car_id;
    int entry_time;
    int parking_duration;
};

/*
struct Car
{
    int car_id;
    unsigned char entry_time;
    unsigned char parking_duration;
    unsigned char parking_fee;
};
*/

struct Car cars[50];

unsigned char operation;
unsigned char program_on=1;




void start(void)
{

    while(program_on)
    {
        printf("1 -> Input Car Information\n2 -> Track Available Spaces\n3 -> Search and Remove a Car\n4 -> Display Parking Lot Status\n5 -> Reversing Entry Order\n6 -> Exit\n");
        scanf("%i", &operation);

        switch(operation)
        {
        case 1:
            unsigned char cars_to_park;
            unsigned char index=0;
            unsigned char car_number=1;
            printf("Enter the number of cars to park: ");
            scanf("%i", &cars_to_park);

            while(cars_to_park != 0)
            {
                printf("Car -> %i\n", car_number+1);
                if(track_spaces() != 0)
                {
                    while(1)
                    {
                        if(cars[index].car_id == 0 && cars[index].entry_time == 0 && cars[index].parking_duration == 0)
                        {
                            int car_id;

                            printf("Enter car ID: ");
                            scanf("%i", &car_id);

                            while(1)
                            {
                                if(car_id <= 0)
                                {
                                    printf("Enter a valid value\nThe car id must be more than 0\n");
                                    printf("Enter car ID: ");
                                    scanf("%i", &car_id);
                                    continue;
                                }
                                unsigned char counter=0;
                                unsigned char id_found=0;
                                while(counter < 50)
                                {
                                    if(car_id == cars[counter].car_id)
                                    {
                                        id_found = 1;
                                    }
                                    counter++;
                                }
                                if(id_found)
                                {
                                    printf("There is already a car in the park with this id, use another one\n");
                                    printf("Enter car ID: ");
                                    scanf("%i", &car_id);
                                }
                                else
                                {
                                    break;
                                }
                            }


                            cars[index].car_id = car_id;

                            printf("Enter entry time (24-hour format): ");
                            scanf("%i", &cars[index].entry_time);

                            while(cars[index].entry_time < 0 || cars[index].entry_time > 24)
                            {
                                cars[index].entry_time = 0;
                                printf("Enter a valid value\nThe entry time must be between 0 and 24\n");

                                printf("Enter entry time (24-hour format): ");
                                scanf("%i", &cars[index].entry_time);
                            }

                            printf("Enter parking duration (in hours): ");
                            scanf("%i", &cars[index].parking_duration);

                            while(cars[index].parking_duration <= 0)
                            {
                                cars[index].parking_duration = 0;
                                printf("Enter a valid value\nThe parking duration must be more than 0\n");

                                printf("Enter parking duration (in hours): ");
                                scanf("%i", &cars[index].parking_duration);
                            }

                            //unsigned char *parking_duration = &cars[car].parking_duration;
                            //cars[car].parking_fee = calculate_fee(parking_duration);
                            //printf("%i\n", cars[car].parking_fee);

                            index++;
                            cars_to_park--;
                            break;
                        }
                        else
                        {
                            index++;
                        }
                    }
                }
                else
                {
                    printf("The park is full\n");
                    break;
                }
                car_number++;
            }
            break;
        case 2:
            printf("Total spaces left: %i\n", track_spaces());
            break;
        case 3:
            if(track_spaces() == 50)
            {
                printf("The park is empty\n");
                continue;
            }
            int car_id;
            printf("Enter car ID to remove: ");
            scanf("%i", &car_id);
            search_car(car_id);
            break;
        case 4:
            if(track_spaces() == 50)
            {
                printf("The park is empty\n");
                continue;
            }
            display_status();
            break;
        case 5:
            if(track_spaces() == 50)
            {
                printf("The park is empty\n");
                continue;
            }
            reverse_entries();
            break;
        case 6:
            program_on=0;
            break;
        default:
            printf("Enter a valid operation: ");
            continue;
        }
    }
    system("cls");
    printf("Thank you for using Smart Parking System Simulation.\n");
    Sleep(3000);
}


unsigned char track_spaces(void)
{
    unsigned char index=0;
    unsigned char spaces=50;
    while(index < 50)
    {
        //printf("car %i -> %i\n",index+1, cars[index].car_id);
        //printf("car %i -> %i\n",index+1, cars[index].entry_time);
        //printf("car %i -> %i\n",index+1, cars[index].parking_duration);
        if(cars[index].car_id != 0 && cars[index].entry_time != 0 && cars[index].parking_duration != 0)
        {
            spaces--;
        }
        index++;
    }
    return spaces;
}


unsigned char calculate_fee(int *parking_duration)
{
    int duration = *parking_duration;
    unsigned char fee = 0;

    //printf("%i\n", parking_duration);
    //printf("%i\n", *parking_duration);
    //printf("%i\n", duration);

    if(duration >= 24)
    {
        return 100;
    }
    while(duration != 0)
    {
        if(duration <= 2)
        {
            fee+=5;
        }
        else if(duration <= 5)
        {
            fee+=3;
        }
        else if(duration < 24)
        {
            fee+=2;
        }
        duration--;
    }
    return fee;
}

void search_car(unsigned char id)
{
    unsigned char index=0;
    //struct Car *cars_addresses=cars;

    while(index < 50)
    {
        if((cars + index) -> car_id == id)
        {
            (cars + index) -> car_id= 0;
            (cars + index) -> entry_time= 0;
            (cars + index) -> parking_duration= 0;
            //(cars + index) -> parking_fee= 0;
            printf("Car removed! Total spaces left: %i\n", track_spaces());
            return;
        }
        index++;
    }
    printf("There is no car with this id in the database, check the id and try again\n");
}

void display_status(void)
{
    unsigned char index=0;
    unsigned char fee=0;
    int *parking_duration;

    while(index < 50)
    {
        parking_duration = &cars[index].parking_duration;
        fee = calculate_fee(parking_duration);

        if((cars+index) -> car_id !=0 && (cars+index) -> parking_duration != 0 && (cars+index) -> entry_time != 0 && fee != 0)
        {
            //printf("%i",fee);

            if(fee == 100)
            {
                printf("%i- Car ID: %i | Parking Duration: %i hours | Fee: $%i (MAX)\n", index, (cars+index) -> car_id, (cars+index) -> parking_duration, fee);
            }
            else
            {
            printf("%i- Car ID: %i | Parking Duration: %i hours | Fee: $%i\n", index, (cars+index) -> car_id, (cars+index) -> parking_duration, fee);
            }
        }
        index++;
    }

}

void reverse_entries(void)
{
    signed char index = 49;
    unsigned char fee=0;
    int *parking_duration;

    printf("Reversed Order of Parked Cars:\n");

    while(index >= 0)
    {
        parking_duration = &cars[index].parking_duration;
        fee = calculate_fee(parking_duration);

        if((cars+index) -> car_id !=0 && (cars+index) -> parking_duration != 0 && (cars+index) -> entry_time != 0 && fee != 0)
        {
            //printf("%i",fee);

            if(fee == 100)
            {
                printf("%i- Car ID: %i | Parking Duration: %i hours | Fee: $%i (MAX)\n", index, (cars+index) -> car_id, (cars+index) -> parking_duration, fee);
            }
            else
            {
            printf("%i- Car ID: %i | Parking Duration: %i hours | Fee: $%i\n", index, (cars+index) -> car_id, (cars+index) -> parking_duration, fee);
            }
        }
        index--;
    }
}

