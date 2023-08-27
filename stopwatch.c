#include <stdio.h>
#include <stdlib.h> //for system()
#include <windows.h> //for Sleep()
#include <conio.h> //for _kbhit() and _getch()

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

int main()
{
    int hours = 0, minutes = 0, seconds = 0;
    DWORD currentTime;

    Stopwatch(hours, minutes, seconds);

    while (1)
    {
        currentTime = GetTickCount();

        // Update the stopwatch
        if (!paused)
        {
            if (currentTime - startTime >= 1000)
            {
                startTime = currentTime;
                seconds++;

                if (seconds >= 60)
                {
                    seconds = 0;
                    minutes++;

                    if (minutes >= 60)
                    {
                        minutes = 0;
                        hours++;
                    }
                }

                lastShownHours = hours;
                lastShownMinutes = minutes;
                lastShownSeconds = seconds;
                Stopwatch(hours, minutes, seconds);
            }
        }

        // Handle user input
        if (_kbhit()) {
            char key = _getch();
            if (key == 'p' || key == 'P')
            {
                if (!paused)
                {
                    paused = 1; // Pause the stopwatch
                    pauseStart = currentTime;
                }
            }
            else if (key == 'r' || key == 'R')
            {
                if (paused)
                {
                    paused = 0; // Resume the stopwatch
                    pauseDuration += currentTime - pauseStart;
                }
            }
            else if (key == 's' || key == 'S')
            {
                // Reset the stopwatch and timestamps
                paused = 0;
                startTime = GetTickCount();
                pauseStart = 0;
                pauseDuration = 0;
                hours = 0;
                minutes = 0;
                seconds = 0;
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

        // Update the display
        Stopwatch(lastShownHours, lastShownMinutes, lastShownSeconds);
    }

    return 0;
}
