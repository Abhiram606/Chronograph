#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void worldClock(char* timezone)
{
    int hour_offset, minute_offset;
    time_t now;

    // Determine the hour and minute offset based on the selected timezone
    if (strcmp(timezone, "IST") == 0)
    {
        hour_offset = 0; //Assume local time is IST
        minute_offset = 0;
    }
    else if (strcmp(timezone, "EST") == 0)
    {
        hour_offset = -9;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "CST") == 0)
    {
        hour_offset = -10;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "MST") == 0)
    {
        hour_offset = -11;
        minute_offset = -30;
    }
    else if (strcmp(timezone, "PST") == 0)
    {
        hour_offset = -12;
        minute_offset = -30;
    }
    else
    {
        printf("Invalid Time Zone \n");
        return;
    }

    struct tm* local_timeinfo;
    now = time(0);
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

int main()
{
    char timezone[10];

    // Prompt user to enter the desired time zone
    printf("Enter the time zone (IST, EST, CST, MST, PST): ");
    scanf("%s", timezone);

    // Call the worldClock function to display time and date
    worldClock(timezone);

    return 0;
}
