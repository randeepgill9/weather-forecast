#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to store weather metrics
typedef struct {
    char day_name[12];
    int temp_celsius;
    int humidity;
    int wind_speed;
    char condition[20];
} WeatherData;

// Function prototypes
void generate_forecast(WeatherData forecast[], int days);
void display_dashboard(const char* city, WeatherData forecast[], int days);
void show_detailed_day(WeatherData forecast[], int day_index);

int main() {
    int choice;
    char city[50];
    int total_days = 5;
    WeatherData forecast[5];

    // Seed the random number generator for dynamic conditions
    srand(time(NULL));

    printf("=========================================\n");
    printf("   CLI WEATHER FORECAST APPLICATION      \n");
    printf("=========================================\n");
    printf("Enter city name: ");
    fgets(city, sizeof(city), stdin);
    city[strcspn(city, "\n")] = '\0'; // Remove newline character

    // Generate weather dataset
    generate_forecast(forecast, total_days);

    while (1) {
        display_dashboard(city, forecast, total_days);
        printf("\nSelect an option:\n");
        printf("[1-5] View detailed hourly/metric report for that day\n");
        printf("[0]   Exit Application\n");
        printf("Enter choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Exiting.\n");
            break;
        }

        if (choice == 0) {
            printf("\nThank you for using the Weather App!\n");
            break;
        } else if (choice >= 1 && choice <= total_days) {
            show_detailed_day(forecast, choice - 1);
        } else {
            printf("\nError: Invalid day selected. Please try again.\n");
        }
    }

    return 0;
}

// Populates arrays with realistic variable variations
void generate_forecast(WeatherData forecast[], int days) {
    const char* days_of_week[] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};
    const char* conditions[] = {"Sunny", "Partly Cloudy", "Rainy", "Heavy Storms", "Overcast", "Foggy"};

    // Get current calendar day index to align output names dynamically
    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    int current_day_idx = tm_info->tm_wday - 1; // 0 = Monday (adjusted)
    if (current_day_idx < 0) current_day_idx = 6;

    for (int i = 0; i < days; i++) {
        strcpy(forecast[i].day_name, days_of_week[(current_day_idx + i) % 7]);
        forecast[i].temp_celsius = rand() % 20 + 15;     // Range: 15°C to 34°C
        forecast[i].humidity = rand() % 40 + 50;         // Range: 50% to 89%
        forecast[i].wind_speed = rand() % 25 + 5;        // Range: 5 km/h to 29 km/h
        strcpy(forecast[i].condition, conditions[rand() % 6]);
    }
}

// Renders clean, tabular visual interfaces in CLI
void display_dashboard(const char* city, WeatherData forecast[], int days) {
    printf("\n---------------------------------------------------------\n");
    printf(" CURRENT & 5-DAY WEATHER FORECAST FOR: %s \n", city);
    printf("---------------------------------------------------------\n");
    printf("%-4s | %-10s | %-6s | %-8s | %-14s\n", "ID", "Day", "Temp", "Humidity", "Condition");
    printf("---------------------------------------------------------\n");

    for (int i = 0; i < days; i++) {
        printf("[%d]  | %-10s | %2d°C   | %-7d%% | %-14s\n",
               i + 1,
               forecast[i].day_name,
               forecast[i].temp_celsius,
               forecast[i].humidity,
               forecast[i].condition);
    }
    printf("---------------------------------------------------------\n");
}

// Simulates micro-variations for expanded specific insights
void show_detailed_day(WeatherData forecast[], int day_index) {
    WeatherData day = forecast[day_index];
    int fahrenheit = (day.temp_celsius * 9 / 5) + 32;

    printf("\n=========================================\n");
    printf(" DETAILED METRICS FOR: %s\n", day.day_name);
    printf("=========================================\n");
    printf(" -> Condition Summary   : %s\n", day.condition);
    printf(" -> Thermal Reading     : %d°C (%d°F)\n", day.temp_celsius, fahrenheit);
    printf(" -> Relative Humidity   : %d%%\n", day.humidity);
    printf(" -> Wind Velocity       : %d km/h\n", day.wind_speed);
    printf(" -> UV Exposure Index   : %d/10\n", (rand() % 6) + 1);
    printf(" -> Precipitation Risk  : %d%%\n", (strcmp(day.condition, "Rainy") == 0 || strcmp(day.condition, "Heavy Storms") == 0) ? (rand() % 30 + 70) : (rand() % 20));
    printf("=========================================\n");
    printf("Press Enter to return to dashboard...");
    getchar(); // Catch buffer leftover
    getchar(); // Hold window
}

