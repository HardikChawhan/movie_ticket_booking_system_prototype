// 0 represents an available seat
// X represents not available seat(while printing)
// 1 represents seat is booked
// one ticket price is Rs.150/-

#include <stdio.h>
#include <stdlib.h>

#define NUM_ROWS 7
#define SEATS_PER_ROW 10
#define TICKET_PRICE 150

void initializing_seating_arrangement(int seat[][SEATS_PER_ROW])
{
    for (int i = 0; i < NUM_ROWS; i++)
    {
        for (int j = 0; j < SEATS_PER_ROW; j++)
        {
            seat[i][j] = 0;
        }
    }
}

void display_seats(int seat[][SEATS_PER_ROW])
{
    printf("SEATING CHART : \n");
    for (int i = 0; i < NUM_ROWS; i++)
    {
        printf("row no %d : ", i + 1);
        for (int j = 0; j < SEATS_PER_ROW; j++)
        {
            if (seat[i][j] == 0)
            {
                printf("0 "); // seat is available
            }
            else
            {
                printf("X "); // seat is not abailable
            }
        }
        printf("\n");
    }
}

int booking_seat(int seat_char[][SEATS_PER_ROW], int row, int seat)
{
    if (row < 1 || seat < 1 || row > NUM_ROWS || seat > SEATS_PER_ROW)
    {
        printf("Invalid Seat or Row number");
        return 0;
    }

    if (seat_char[row - 1][seat - 1] == 0) // -1 because we are running the loop from 0 and not 1
    {
        seat_char[row - 1][seat - 1] = 1; // -1 because we are running the loop from 0 and not 1
        printf("Seat in row %d , seat %d is booked\n", row, seat);
        return 1;
    }
    else
    {
        printf("Seat in row %d , seat %d is already booked : \n", row, seat);
        return 0;
    }
}

int bookSeatsLimit(int chart[][SEATS_PER_ROW], int numSeats)
{
    int seatsBooked = 0;
    int row, seat;
    // eg of how this will work
    // 0            4
    // 1            4
    // 2            4
    // 3            4
    while (seatsBooked < numSeats)
    {
        printf("Enter the row and seat number to book (e.g., 3 5): ");
        scanf("%d %d", &row, &seat);
        if (booking_seat(chart, row, seat) == 1)
        {
            seatsBooked++;
        }
    }
    return seatsBooked;
    printf("\n");
}

void total_price(int seat)
{
    int total = seat * TICKET_PRICE;
    printf("Total price for %d Seat(s) is Rs.%d/- \n", seat, total);
    printf("\n");
}

void meanu(int choice, int seat, int chart[][SEATS_PER_ROW])
{

    printf("\nWarning! per person only 1 booking is considered\n");

    do
    {
        printf("\nMenu:\n");
        printf("1. Display seating chart\n");
        printf("2. Book a seat\n");
        printf("3. see the total price\n");
        printf("4. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            display_seats(chart);
            break;

        case 2:
            printf("Enter the number of seats to book (upto 5 only): ");
            scanf("%d", &seat);
            if (seat > 0 && seat <= 5)
            {
                int seats_booked = bookSeatsLimit(chart, seat);
                printf("%d Seat(s) Booked \n", seats_booked);
            }
            else
            {
                printf("Enter Valid no of seats (Between 1 and 5)\n");
            }
            break;

        case 3:
            total_price(seat);
            break;

        case 4:
            printf("Exit!\n");
            break;

        default:
            printf("Invalid choice! Please Enter again\n");
            break;
        }

    } while (choice != 4);
}

void save_seating_chart(const char *filename, int chart[][SEATS_PER_ROW])
{
    FILE *file = fopen(filename, "wb");
    if (file == NULL)
    {
        printf("Error opening file for writing\n");
        exit(1);
    }
    fwrite(chart, sizeof(int), NUM_ROWS * SEATS_PER_ROW, file);
    fclose(file);
}

void load_seating_chart(const char *filename, int chart[][SEATS_PER_ROW])
{
    FILE *file = fopen(filename, "rb");
    if (file == NULL)
    {
        printf("Seating chart file not found. Initializing a new seating chart.\n");
        initializing_seating_arrangement(chart);
    }
    else
    {
        fread(chart, sizeof(int), NUM_ROWS * SEATS_PER_ROW, file);
        fclose(file);
    }
}

int main()
{

    int chart_1030_1230[NUM_ROWS][SEATS_PER_ROW];
    int chart_1_3[NUM_ROWS][SEATS_PER_ROW];
    int chart_430_630[NUM_ROWS][SEATS_PER_ROW];
    int chart_7_9[NUM_ROWS][SEATS_PER_ROW];
    initializing_seating_arrangement(chart_1030_1230);
    initializing_seating_arrangement(chart_1_3);
    initializing_seating_arrangement(chart_430_630);
    initializing_seating_arrangement(chart_7_9);

    load_seating_chart("seating_chart_1030_1230.dat", chart_1030_1230);
    load_seating_chart("seating_chart_1_3.dat", chart_1_3);
    load_seating_chart("seating_chart_430_630.dat", chart_430_630);
    load_seating_chart("seating_chart_7_9.dat", chart_7_9);

    int seat, choice;
    int choose;

    do
    {
        printf("\nChoose Timings\n");
        printf("1. 10:30 - 12:30\n");
        printf("2. 1:00 - 3:00\n");
        printf("3. 4:30 - 6:30\n");
        printf("4. 7:00 - 9:00\n");
        printf("5. quit\n");
        printf("Enter your choice : ");
        scanf("%d", &choose);

        switch (choose)
        {
        case 1:

            meanu(choice, seat, chart_1030_1230);
            break;

        case 2:

            meanu(choice, seat, chart_1_3);
            break;

        case 3:

            meanu(choice, seat, chart_430_630);
            break;

        case 4:

            meanu(choice, seat, chart_7_9);
            break;

        case 5:
            printf("Quit!\n");
            break;
        default:
            printf("Please choose from the timigs above\n");
            break;
        }

    } while (choose != 5);

    save_seating_chart("seating_chart_1030_1230.dat", chart_1030_1230);
    save_seating_chart("seating_chart_1_3.dat", chart_1_3);
    save_seating_chart("seating_chart_430_630.dat", chart_430_630);
    save_seating_chart("seating_chart_7_9.dat", chart_7_9);

    return 0;
}