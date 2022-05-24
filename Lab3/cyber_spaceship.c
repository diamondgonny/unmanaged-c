#include "cyber_spaceship.h"


const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    /* CAB의 시작주소를 const char 포인터형의 ptr가 빌려와서 알고리즘에 활용할 것임 */
    size_t i;
    size_t j;
    size_t cluster_overlap = 0u;
    size_t safe_score = 0u;
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

    /* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
    /* ↑                                                    */
    /* 가리키는 포인터 ptr를 한칸씩 이동, 거기엔 클러스터가 얼마나 있는지 조사 */
    /* 만약, 해당 ptr 위치에 클러스터 있으면 그 갯수만큼 ++cluster_overlap */
    /* 그 위치 safe 판정 -> 만약 누적된 (연속) safe_score가 최고점수이면... */
    /* *(out_longest_safe_area_length)와 longest_safe_zone_start_address는 갱신함 */
    for (i = 0; i < cab_length; ++i) {
        for (j = 0; j < cluster_count; ++j) {
            if (cluster_start_locations[j] <= ptr && ptr < cluster_start_locations[j] + cluster_lengths[j]) {
                ++cluster_overlap;
            } 
        }
        cluster_overlap % 2 != 0 ? safe_score = 0 : ++safe_score;
        if (safe_score >= *(out_longest_safe_area_length)) {
            *(out_longest_safe_area_length) = safe_score;
            longest_safe_zone_start_address = ptr - safe_score + 1;
        }
        ++ptr;
        cluster_overlap = 0;
    }

    /* 정답 반환 */
    return longest_safe_zone_start_address;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{
    /* CAB의 시작주소를 const char 포인터형의 ptr가 빌려와서 알고리즘에 활용할 것임 */
    size_t i;
    size_t j;
    size_t cluster_overlap = 0u;
    size_t danger_zone = 0u;
    size_t safe_zone = 0u;
    const char* ptr = cab_start_location;
    double travel_time = 0;

    /* 예외 */
    if (cluster_count == 0) {
        cluster_start_locations = NULL;
        cluster_lengths = NULL;
        travel_time = 0.1 * cab_length;
        return (int)(travel_time + 0.5);
    }

    /* ㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡㅡ */
    /* ↑                                                    */
    /* 가리키는 포인터 ptr를 한칸씩 이동, 거기엔 클러스터가 얼마나 있는지 조사 */
    /* 만약, 해당 ptr 위치에 클러스터 있으면 그 갯수만큼 ++cluster_overlap */
    /* 그 위치 safe 혹은 danger 판정 -> (끝날 때까지 반복...) -> 총 예상 소요시간 계산 */
    for (i = 0; i < cab_length; ++i) {
        for (j = 0; j < cluster_count; ++j) {
            if (cluster_start_locations[j] <= ptr && ptr < cluster_start_locations[j] + cluster_lengths[j]) {
                ++cluster_overlap;
            }
        }
        cluster_overlap % 2 != 0 ? ++danger_zone : ++safe_zone;
        ++ptr;
        cluster_overlap = 0;
    }

    /* 정답 반환 */
    travel_time = 0.2 * danger_zone + 0.1 * safe_zone;
    return (int)(travel_time + 0.5);
}
