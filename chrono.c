#include <stdio.h>
#include <stdlib.h> //for system()
#include <windows.h> //for Sleep()
#include <conio.h> //for _kbhit() and _getch()
#include <time.h>
#include <string.h>

int paused = 0;
DWORD startTime = 0;
DWORD pauseStart = 0;
DWORD pauseDuration = 0;
int lastShownHours = 0, lastShownMinutes = 0, lastShownSeconds = 0;
int displayTimestamp = 0;

// Define a structure to store timestamps
typedef struct {
    int hours;
    int minutes;
    int seconds;
} Timestamp;

Timestamp timestamps[100]; // Store up to 100 timestamps
int timestampCount = 0;

// Function to implement the timer
void timer(int hour, int minutes, int seconds, int init_hour, int init_minutes, int init_seconds)
{
    // Display instructions to the user
    printf("Press 'p' to pause, 'r' to resume, and 's' to restart.\n");

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
                paused = 1; // Toggle pause state
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

// Function to implement the world clock
void worldClock(char* timezone)
{
    int hour_offset, minute_offset;
    time_t now;

    // Determine the hour and minute offset based on the selected timezone
    if (strcmp(timezone, "IST") == 0 || strcmp(timezone, "ist") == 0)
    {
        hour_offset = 0; //Assume local time is IST
        minute_offset = 0;
    }
    else if (strcmp(timezone, "EST") == 0 || strcmp(timezone, "est") == 0)
    {
        hour_offset = -9;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "CST") == 0 || strcmp(timezone, "cst") == 0)
    {
        hour_offset = -10;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "MST") == 0 || strcmp(timezone, "mst") == 0)
    {
        hour_offset = -11;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "PST") == 0 || strcmp(timezone, "pst") == 0)
    {
        hour_offset = -12;
        minute_offset = -30;
    }
    else
    {
        printf("Invalid Time Zone \n");
        return;
    }

    now = time(0);
    struct tm* local_timeinfo;
    local_timeinfo = localtime(&now);

    // Apply the offset to the time
    local_timeinfo->tm_hour += hour_offset;
    local_timeinfo->tm_min += minute_offset;

    // Adjust for changes to the day
    mktime(local_timeinfo);

    char buffer[80];
    strftime(buffer, 80, "%I:%M %p", local_timeinfo); // Time format
    printf("The current time in %s is: %s (%c%02d:%02d hours)\n", timezone, buffer, (hour_offset >= 0) ? '+' : '-', abs(hour_offset), abs(minute_offset));

    strftime(buffer, 80, "%Y-%m-%d", local_timeinfo); // Date format
    printf("The date in %s is: %s\n", timezone, buffer);
}

// Function to display the stopwatch and timestamps
void Stopwatch(int hours, int minutes, int seconds)
{   
    system("cls");
    printf("%02d:%02d:%02d\n", hours, minutes, seconds);
    for (int i = 0; i < timestampCount; i++) {
        printf("#%d: %02d:%02d:%02d\n", i + 1, timestamps[i].hours, timestamps[i].minutes, timestamps[i].seconds);
    }
}

// Function to add a new timestamp
void PrintTimestamp(int hours, int minutes, int seconds)
{
    if (timestampCount < 100) {
        timestamps[timestampCount].hours = hours;
        timestamps[timestampCount].minutes = minutes;
        timestamps[timestampCount].seconds = seconds;
        timestampCount++;
    }
}

// Function to handle user input (pausing, resuming, resetting, and adding timestamps)
void HandleInput()
{
    if (_kbhit()) {
        char key = _getch();
        if (key == 'p' || key == 'P')
        {
            if (!paused)
            {
                paused = 1; // Pause the stopwatch
                pauseStart = GetTickCount(); // Record the pause start time
            }
        }
        else if (key == 'r' || key == 'R')
        {
            if (paused)
            {
                paused = 0; // Resume the stopwatch
                pauseDuration += GetTickCount() - pauseStart; // Accumulate pause time
            }
        }
        else if (key == 's' || key == 'S')
        {
            // Reset the stopwatch and timestamps
            paused = 0;
            startTime = GetTickCount();
            pauseStart = 0;
            pauseDuration = 0;
            lastShownHours = 0;
            lastShownMinutes = 0;
            lastShownSeconds = 0;
            displayTimestamp = 0;
            timestampCount = 0;
        }
        else if (key == 13) // Enter key
        {
            // Add a new timestamp
            PrintTimestamp(lastShownHours, lastShownMinutes, lastShownSeconds);
        }
    }
}

// Function to update the stopwatch display
void UpdateStopwatch()
{
    DWORD currentTime = GetTickCount();

    if (!paused)
    {
        if (currentTime - startTime >= 1000)
        {
            startTime = currentTime;
            lastShownSeconds++;

            if (lastShownSeconds >= 60)
            {
                lastShownSeconds = 0;
                lastShownMinutes++;

                if (lastShownMinutes >= 60)
                {
                    lastShownMinutes = 0;
                    lastShownHours++;
                }
            }

            // Update the display
            Stopwatch(lastShownHours, lastShownMinutes, lastShownSeconds);
        }
    }
}

int main()
{
    int choice, hour, minutes, seconds;
    char timezone[10];
    int init_hour, init_minutes, init_seconds;

    // Display menu to the user
    printf("What do you want to open:\n");
    printf("1. Timer\n");
    printf("2. World Clock\n");
    printf("3. Stopwatch\n");
    scanf("%d", &choice); // Get user's choice

    switch (choice)
    {
        case 1: // Timer functionality

            // Get initial time from the user
            printf("Enter hours: "); scanf("%d", &hour);
            printf("Enter minutes: "); scanf("%d", &minutes);
            printf("Enter seconds: "); scanf("%d", &seconds);

            // Used when the timer is reset
            init_hour = hour;
            init_minutes = minutes;
            init_seconds = seconds;

            // Call the timer function
            timer(hour, minutes, seconds, init_hour, init_minutes, init_seconds);
            break;

        case 2: // World Clock functionality

            // Prompt user to enter the desired time zone
            printf("Enter the time zone (IST, EST, CST, MST, PST): "); 
            scanf("%s", timezone);

            // Call the worldClock function
            worldClock(timezone);
            break;

case 3: // Stopwatch functionality

  // Initial display of the stopwatch
  Stopwatch(lastShownHours, lastShownMinutes, lastShownSeconds);

  // Print instructions for stopwatch controls
  printf("Press 'p' to pause, 'r' to resume, and 's' to restart.\n");

  while (1) {
    // Continuously update the stopwatch and handle user input
    UpdateStopwatch();
    HandleInput();
  }
  break;


        default:
            // Invalid choice
            printf("Invalid choice!\n");
            break;
    }

    return 0;
}
