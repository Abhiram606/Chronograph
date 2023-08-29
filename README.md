![Screenshot 2023-08-29 184920](https://github.com/karts13/Chronograph/assets/126340629/0136263a-15b4-4a0a-91c2-117fbf881004)## Personal details

> **Name:** A Karthik Shneoy
> 
> **USN:** 4NM21CM002
> 
> Computer and Communication Engineering
> 
> N.M.A.M. Institute of Technology, Nitte
> 
> **Email:** karthishenoy2014@gmail.com

# Chronograph

## Description
> The Timer, the World Clock, and the Stopwatch are three unique features of this C program *Chronograph*, which includes a flexible time-related utility. Users can choose one of these features from the program's user-friendly interface and can interact with each part as follows:
> 1. Timer Functionality:
>    Users can set a countdown timer using this functionality. Users enter hours, minutes, and seconds, and the timer counts down in real-time, displaying the amount of time left in the format "HH:MM:SS." The timer is pauseable and reversible by users. The application announces "Time's up!!" when the counter reaches zero.
> 2. World Clock Functionality:
>    Users can view the current time and date in several time zones with this functionality. The code calculates and displays the corresponding local time and date when a time zone abbreviation (IST, EST, CST, MST, PST) is chosen.
> 3. Stopwatch Functionality:
>    Users can calculate elapsed time using the stopwatch. Hours, minutes, and seconds are shown on the display in the following format: "HH:MM:SS." The stopwatch can be reset, paused, and continued by users. Furthermore, they can record timestamps by pressing the Enter key and saving them for later use.

## How to Use this Code
> 1. Create a new text file with a ".c" extension, e.g., `chrono.c`.
> 2. Copy the code from [chrono.c](https://github.com/karts13/Chronograph/blob/main/chrono.c) repository and paste it into the text editor.
> 3. Compile the code using a C compiler such as GCC (GNU Compiler Collection) or any other compilers.
> 4. Do the necessary [customizations](https://github.com/karts13/Chronograph/blob/main/README.md#customization).
> 5. After successful compilation, an executable file named `chrono` will be generated. Run the compiled executable
> 6. Upon running the program, a menu will be displayed with three options shown in .....
> 7. Enter the number corresponding to your desired functionality and press Enter.
> 8. Follow the prompts for each selected functionality as described in the previous instructions:
>    * For the Timer, input the countdown duration and interact with the timer using 'p', 'r', and 's' keys.
>    * For the World Clock, input a time zone abbreviation and view the current time and date.
>    * For the Stopwatch, interact with the stopwatch using 'p', 'r', 's', and Enter key.
> 9. To exit the program, you can press `Ctrl+C` in the terminal where the program is running.


## Customization 
> This code can be easily customized to meet your specific needs. Here are some things you may want to modify:
> * **Time Units:** Adjust the code to work with different time units (e.g., milliseconds, centiseconds) instead of seconds.
> * **Custom Time Zones:** Add more time zones and corresponding offsets to the `worldClock` function.
> * **Time Formatting:** Modify the formatting of displayed time, such as showing fractions of seconds or using a 24-hour time format.
> * **Add Sounds:** Integrate sound effects for specific events, such as when the timer reaches zero or when a timestamp is captured.
> * **Timestamp Limit:** Change the maximum limit of timestamps stored in the Stopwatch to any desired value.


## Sample Outputs
> ![Text Editor](https://github.com/karts13/Chronograph/assets/126340629/42ec6c8b-b94d-4131-a13d-c2df02daa7ff)
> :--:
> <b>Text Editor</b>
>
> ![Menu](https://github.com/karts13/Chronograph/assets/126340629/e7aaca37-6ef6-4df4-9659-85e9447431fc)
> :--:
> <b>Chronograph Menu</b>
>
> ![Timer](https://github.com/karts13/Chronograph/assets/126340629/d2237940-de27-4106-907f-58d57c5a9bcf)
> :--:
> <b>Timer</b>
>
> ![World Clock](https://github.com/karts13/Chronograph/assets/126340629/0313d068-2f61-403b-a352-abd71a80c98b)
> :--:
> <b>World Clock</b>
>
> ![Stopwatch](https://github.com/karts13/Chronograph/assets/126340629/dfd7dbf9-252d-4c67-91cc-4c8c87e0d03c)
> :--:
> <b>Stopwatch with Timestamps</b>
