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
    #include <stdio.h>
    #include "cyber_spaceship.h"


    const char* get_longest_safe_zone_or_null(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count, size_t* out_longest_safe_area_length)
    {
        size_t i;
        size_t j;
        size_t a = 0;
        size_t safe_score = 0;
        const char* p = cab_start_location;
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
                if (p >= cluster_start_locations[j] && p - cluster_start_locations[j] < cluster_lengths[j]) {
                    a++;
                } 
            }
            a % 2 != 0 ? safe_score = 0 : safe_score++;
            if(safe_score >= *(out_longest_safe_area_length)) {
                *(out_longest_safe_area_length) = safe_score;
                longest_safe_zone_start_address = p - safe_score + 1;
            }
            p++;
            a = 0;
        }

        /* 정답 반환 */
        return longest_safe_zone_start_address;
    }

    int get_travel_time(const char* const cab_start_location, const size_t cab_length, const char* const cluster_start_locations[], const size_t cluster_lengths[], const size_t cluster_count)
    {

        size_t i;
        size_t j;
        size_t a = 0;
        size_t danger_zone = 0;
        size_t safe_zone = 0;
        const char* p = cab_start_location;
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
                if (p >= cluster_start_locations[j] && p - cluster_start_locations[j] < cluster_lengths[j]) {
                    a++;
                } 
            }
            a % 2 != 0 ? danger_zone++ : safe_zone++;
            p++;
            a = 0;
        }

        /* zone별 시간 연산, 정답 반환 */
        travel_time = 0.2 * danger_zone + 0.1 * safe_zone;
        return (int)(travel_time + 0.5);
    }
