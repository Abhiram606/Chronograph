#include <stdio.h>
#include <stdlib.h> //for system()
#include <windows.h> //for Sleep()
#include <conio.h> //for _kbhit() and _getch()

int paused = 0;

// Function to implement the timer
void timer(int hour, int minutes, int seconds, int init_hour, int init_minutes, int init_seconds)
{
    // Display instructions to the user
    printf("Press 'p' to pause, 'r' to resume, and 's' to restart. \n");

    // Main loop for the timer
    while (1)
    {
        // Check if the timer has reached zero
        if (hour == 0 && minutes == 0 && seconds == 0)
        {
            break;
        }

        // Check if the timer is not paused
        if (!paused)
        {
            // Update minutes and hours if seconds or minutes reach zero
            if (seconds == 0 && minutes == 0)
            {
                minutes = 60;
                hour--;
            }
            if (seconds == 0)
            {
                seconds = 60;
                minutes--;
            }

            // Clear the line and print the timer in the same line
            printf("\r%d:%02d:%02d", hour, minutes, seconds--);
            Sleep(1000); // Pause for 1 second
        }

        // Check if a key has been pressed
        if (_kbhit()) {
            char key = _getch();
            if (key == 'p' || key == 'P')
            {
                paused = 1 - paused; // Toggle pause state
            }
            else if (key == 'r' || key == 'R')
            {
                paused = 0; // Resume the timer
            }
            else if (key == 's' || key == 'S')
            {
                paused = 0; // Reset the pause state
                hour = init_hour; // Reset to initial values
                minutes = init_minutes;
                seconds = init_seconds;
            }
        }
    }
    
    // Clear the screen and display time's up message
    system("cls");
    printf("Time's up!!");
}

int main()
{
    int hour, minutes, seconds;

    // Get initial time from the user
    printf("Enter hours: "); scanf("%d", &hour);
    printf("Enter minutes: "); scanf("%d", &minutes);
    printf("Enter seconds: "); scanf("%d", &seconds);

    // Used when the timer is reset
    int init_hour = hour;
    int init_minutes = minutes;
    int init_seconds = seconds;

    // Start the timer
    timer(hour, minutes, seconds, init_hour, init_minutes, init_seconds);

    return 0;
}
