#include "cyber_spaceship.h"


const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    size_t i;
    size_t j;
    size_t cluster_amounts = 0;
    size_t safe_score = 0;
    const char* ptr = cab_start_location;
    const char* longest_safe_zone_start_address = NULL;
    *(out_longest_safe_area_length) = 0;

    /* 예외 */
    if (cab_length == 0) {
        *(out_longest_safe_area_length) = 0;
        return NULL;
    }

    if (cluster_count == 0) {
        cluster_start_locations = NULL;
        cluster_lengths = NULL;
        *(out_longest_safe_area_length) = cab_length;
        return cab_start_location;
    }

    /* 가리키는 포인터 p를 기준으로, 클러스터가 존재하는가? */
    /* 만약에, 현위치에서 qn이 있는지? 있으면 a++, 없으면 x*/
    for (i = 0; i < cab_length; ++i) {
        for(j = 0; j < cluster_count; ++j) {
            if (ptr >= cluster_start_locations[j] && ptr - cluster_start_locations[j] < cluster_lengths[j]) {
                cluster_amounts++;
            } 
        }
        cluster_amounts % 2 != 0 ? safe_score = 0 : safe_score++;
        if(safe_score >= *(out_longest_safe_area_length)) {
            *(out_longest_safe_area_length) = safe_score;
            longest_safe_zone_start_address = ptr - safe_score + 1;
        }
        ptr++;
        cluster_amounts = 0;
    }

    /* 정답 반환 */
    return longest_safe_zone_start_address;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{

    size_t i;
    size_t j;
    size_t cluster_amounts = 0;
    size_t danger_zone = 0;
    size_t safe_zone = 0;
    const char* ptr = cab_start_location;
    double travel_time = 0;

    /* 예외 */
    if (cluster_count == 0) {
        cluster_start_locations = NULL;
        cluster_lengths = NULL;
        travel_time = 0.1 * cab_length;
        return (int)(travel_time + 0.5);
    }

    /* 가리키는 포인터 p를 기준으로, 클러스터가 존재하는가? */
    /* 만약에, 현위치에서 qn이 있는지? 있으면 a++, 없으면 x*/
    for (i = 0; i < cab_length; ++i) {
        for(j = 0; j < cluster_count; ++j) {
            if (ptr >= cluster_start_locations[j] && ptr - cluster_start_locations[j] < cluster_lengths[j]) {
                cluster_amounts++;
            } 
        }
        cluster_amounts % 2 != 0 ? danger_zone++ : safe_zone++;
        ptr++;
        cluster_amounts = 0;
    }

    /* zone별 시간 연산, 정답 반환 */
    travel_time = 0.2 * danger_zone + 0.1 * safe_zone;
    return (int)(travel_time + 0.5);
}
