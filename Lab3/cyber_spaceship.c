/*
 사이버 스페이스(cyberspace, 가상공간)에서 우주탐험선 엔터프라이즈 호를 지휘하는 총사령관인 여러분은 아직 사람의 손길이 닿지 않은 새로운 행성을 찾는 임무를 수행하고 있습니다. 이 임무를 수행하던 도중 사이버 소행성대(CAB, Cyber Asteroid Belt)라고 불리는 무수히 많은 사이버 소행성 클러스터가 있는 지역에 들어가게 되었습니다. CAB 주위에 둥둥 떠다니는 소행성들은 이 지역을 지나가는 우주선들을 파괴하는 주범이지만 타이트한 일정상 우회를 할 수도 없는 상황입니다. 따라서 여러분은 정면 돌파하기로 결단을 내렸습니다. 엔터프라이즈 호의 슈퍼컴퓨터인 데이터(Data)가 소행성 클러스터들을 분석한 뒤 다음의 정보를 제공했습니다.

- CAB의 시작 위치(16진수)와 길이
- CAB 안에 있는 각 소행성 클러스터의 시작 위치(16진수)와 길이
- CAB 안에 있는 소행성 클러스터의 총 개수
- 어떤 위치에서 겹치는(overlap) 소행성 클러스터의 수가 짝수인 경우, 클러스터들이 서로를 상쇄시킴. 따라서 이 위치는 안전한 지역. 소행성 클러스터가 아예 없는 곳도 역시 안전 지역임.
-겹치는 소행성 클러스터의 수가 홀수라면 이 지역은 위험 지역. 어떤 일이 생길지 모르니 조심해야 함.
- 위험 지역은 1분에 5바이트만 항해 가능. 안전 지역은 1분에 10바이트 항해 가능.

이제 엔터프라이즈 호의 뛰어난 승무원들과 함께 여러분이 할 일은 1) CAB 안에 있는 안전 지역 중 가장 긴 것의 위치와 길이, 그리고 2) CAB 전체를 통과할 때 걸리는 시간을 구하는 것입니다.
*/

#include "cyber_spaceship.h"

const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
{
    int i;
    int j;
    size_t safe_score = 0;
    size_t rel_address = 0;
    char cab[CAB_LENGTH] = { 0, };

    /* 예외 */
    if (cluster_count == 0) {
        cluster_start_locations = NULL;
        cluster_lengths = NULL;
    }

    if (cab_length == 0) {
        *(out_longest_safe_area_length) = 0;
        return NULL;
    }

    /* 클러스터 (주소값) 계산, 숫자 주입 */
    for (i = 0; i < cluster_count; ++i) {
        for (j = cluster_start_locations[i] - cab_start_location; j < cluster_lengths[i] + cluster_start_locations[i] - cab_start_location; ++j) {
            cab[j]++;
        }
    }

    /* 안전지역 판정 알고리즘 (Highscore, 끝-시작주소) */
    for (i = 0; i < CAB_LENGTH; ++i) {
        if (cab[i] % 2 == 0) {
            safe_score++;
        }
        else if (*(out_longest_safe_area_length) <= safe_score) {
            *(out_longest_safe_area_length) = safe_score;
            /* 처음주소로부터의 offset을 고려하자 (p + i - s_length) */
            rel_address = (i - safe_score);
            safe_score = 0;
        }
        else {
            safe_score = 0;
        }
    }
    /* 정답 반환 */
    {
        const char* longest_safe_cluster_start_address = cab_start_location + rel_address;
        return longest_safe_cluster_start_address;
    }
    return NULL;
}

int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
{

    int i;
    int j;
    size_t danger_zone = 0;
    size_t safe_zone = 0;
    double travel_time = 0;
    char cab[CAB_LENGTH] = { 0, };

    /* 예외 */
    if (cluster_count == 0) {
        cluster_start_locations = NULL;
        cluster_lengths = NULL;
    }

    /* 클러스터 (주소값) 계산, 숫자 주입 */
    for (i = 0; i < cluster_count; ++i) {
        for (j = cluster_start_locations[i] - cab_start_location; j < cluster_lengths[i] + cluster_start_locations[i] - cab_start_location; ++j) {
            cab[j]++;
        }
    }

    /* 안전지역 판정 알고리즘 */
    for (i = 0; i < CAB_LENGTH; ++i) {
        cab[i] % 2 == 0 ? safe_zone++ : danger_zone++;
    }

    /* zone별 시간 연산, 정답 반환 */
    travel_time = 0.2 * danger_zone + 0.1 * safe_zone;
    return (int)(travel_time + 0.5);
}
