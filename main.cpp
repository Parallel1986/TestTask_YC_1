#include <iostream>
#include <ctime>
#include <string>
struct tm_m {
    int tm_sec = 0;
    int tm_min = 0;    
    int tm_hour = 0;
    int tm_mday = 0;
    int tm_mon = 0;
    int tm_year = 0;
};

enum SECONDS {
    IN_HOUR = 3600,
    IN_DAY = 86400,
    IN_LONG_MONTH = 2678400,
    IN_SHORT_MONTH = 2592000,
    IN_FEBRUARY = 2419200,
    IN_YEAR = 31536000
};


std::time_t calculateSeconds(tm_m&amp; time) {
    std::time_t total_time = 0;

    total_time += time.tm_sec;
    total_time += time.tm_min * 60;
    total_time += time.tm_hour * SECONDS::IN_HOUR;

    total_time += time.tm_mday * SECONDS::IN_DAY;
    --time.tm_mon;
    for (int month = time.tm_mon; month > 0; --month){
        if (month == 2) {
            total_time += SECONDS::IN_FEBRUARY;
        }
        else if (month == 1 || month == 3 || month == 5
           || month == 7 || month == 8 || month == 10
           || month == 12) {
            total_time += SECONDS::IN_LONG_MONTH;
        }
        else {
            total_time += SECONDS::IN_SHORT_MONTH;
        }
    }

    total_time += (std::time_t)SECONDS::IN_YEAR * time.tm_year;
    return total_time;
}

std::string calculateTime(const std::time_t&amp; time) {
    std::time_t days = time / SECONDS::IN_DAY;
    std::time_t seconds = time % SECONDS::IN_DAY;
    std::string out = std::to_string(days) + " " + std::to_string(seconds);
    return out;
}


int main() {
    std::string out;
    
    tm_m start, end;

    std::cin >> start.tm_year >> start.tm_mon >> start.tm_mday >> start.tm_hour >> start.tm_min >> start.tm_sec;
    std::cin >> end.tm_year >> end.tm_mon >> end.tm_mday >> end.tm_hour >> end.tm_min >> end.tm_sec;
    
    std::time_t exist_time;
    
    end.tm_year -= start.tm_year;
    start.tm_year = 0;
    
    exist_time = calculateSeconds(end) - calculateSeconds(start);
    
    out = calculateTime(exist_time);
    
    std::cout << out;
    
    return 0;
}
