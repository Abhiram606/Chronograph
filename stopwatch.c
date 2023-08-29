#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>

int paused = 0;
DWORD startTime = 0;
DWORD pauseStart = 0;
DWORD pauseDuration = 0;
int lastShownHours = 0, lastShownMinutes = 0, lastShownSeconds = 0;
int displayTimestamp = 0;

typedef struct {
    int hours;
    int minutes;
    int seconds;
} Timestamp;

Timestamp timestamps[100];
int timestampCount = 0;

void Stopwatch(int hours, int minutes, int seconds)
{
    system("cls");
    printf("%02d:%02d:%02d\n", hours, minutes, seconds);
    for (int i = 0; i < timestampCount; i++) {
        printf("#%d: %02d:%02d:%02d\n", i + 1, timestamps[i].hours, timestamps[i].minutes, timestamps[i].seconds);
    }
}

void PrintTimestamp(int hours, int minutes, int seconds)
{
    if (timestampCount < 100) {
        timestamps[timestampCount].hours = hours;
        timestamps[timestampCount].minutes = minutes;
        timestamps[timestampCount].seconds = seconds;
        timestampCount++;
    }
}

void HandleInput()
{
    if (_kbhit()) {
        char key = _getch();
        if (key == 'p' || key == 'P')
        {
            if (!paused)
            {
                paused = 1;
                pauseStart = GetTickCount();
            }
        }
        else if (key == 'r' || key == 'R')
        {
            if (paused)
            {
                paused = 0;
                pauseDuration += GetTickCount() - pauseStart;
            }
        }
        else if (key == 's' || key == 'S')
        {
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
            PrintTimestamp(lastShownHours, lastShownMinutes, lastShownSeconds);
        }
    }
}

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

            Stopwatch(lastShownHours, lastShownMinutes, lastShownSeconds);
        }
    }
}

int main()
{
    int hours = 0, minutes = 0, seconds = 0;

    Stopwatch(hours, minutes, seconds);

    while (1)
    {
        UpdateStopwatch();
        HandleInput();
    }

    return 0;
}
