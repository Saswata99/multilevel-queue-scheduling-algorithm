#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

struct process{
    int p_id;
    int burst_time;
    int arrival_time;
    int priority;
    int response_time;
    int completion_time;
    int remaining_time;
    bool response_time_flag;
};


int time = 0, time_quantum = 4;

struct process queue_1[50];     // lowest range of priority
struct process queue_2[50];     // medium range of priority
struct process queue_3[50];     // highest range of priority

int q_1_index = 0;
int q_2_index = 0;
int q_3_index = 0;

int q_1_count = 0;
int q_2_count = 0;
int q_3_count = 0;

int q_1_range = 4;        // range : 1-4
int q_2_range = 7;        // range : 5-7
int q_3_range = 10;        // range : 8-10

int time_quantum_scheduler = 10;
int round_robin_flag = 0;

int comp_arrival_time(struct process * a, struct process * b) {
    return ( a->arrival_time - b->arrival_time);
}

int comp_priority(struct process * a, struct process * b) {
    return ( b->priority - a->priority);
}

void round_robin(){
    int x = time+10;

    while(round_robin_flag != q_3_count){
        if (queue_3[q_3_index].remaining_time != 0){

            if (!queue_3[q_3_index].response_time_flag) {
                queue_3[q_3_index].response_time = time;
                queue_3[q_3_index].response_time_flag = true;
            }

            round_robin_flag = 0;
            int y;

            if (queue_3[q_3_index].remaining_time >= time_quantum){
                y = 4;
            }
            else{
                y = queue_3[q_3_index].remaining_time;
            }

            if ((time + y) <= x) {
                printf("\n   Process(PID : %d)  run for %d", queue_3[q_3_index].p_id, y);
                time += y;
                queue_3[q_3_index].remaining_time -= y;

                if (!queue_3[q_3_index].remaining_time){
                    queue_3[q_3_index].completion_time = time;
                }
                q_3_index = (q_3_index+1)%q_3_count;

            } else if (x - time != 0) {
                printf("\n   Process(PID : %d)  run for %d", queue_3[q_3_index].p_id, x - time);
                queue_3[q_3_index].remaining_time -= (x - time);
                time = x;
                break;
            } else {
                break;
            }
        }
        else{
            q_3_index = (q_3_index+1)%q_3_count;
            round_robin_flag ++;
        }
    }

}

void priority(){
    int x = time+time_quantum_scheduler;

    while(q_2_index < q_2_count){
        if (!queue_2[q_2_index].response_time_flag){
            queue_2[q_2_index].response_time = time;
            queue_2[q_2_index].response_time_flag = true;
        }

        if ((time + queue_2[q_2_index].remaining_time) <= x){
            printf("\n   Process(PID : %d)  run for %d" ,queue_2[q_2_index].p_id, queue_2[q_2_index].remaining_time);
            time += queue_2[q_2_index].remaining_time;
            queue_2[q_2_index].remaining_time = 0;
            queue_2[q_2_index].completion_time = time;
            q_2_index ++;
        }
        else if (x-time != 0){
            printf("\n   Process(PID : %d)  run for %d" ,queue_2[q_2_index].p_id, x-time);
            queue_2[q_2_index].remaining_time -= (x-time);
            time = x;
            break;
        }
        else{
            break;
        }
    }
}

void fcfs(){
    int x = time+10;

    while(q_1_index < q_1_count){
        if (!queue_1[q_1_index].response_time_flag){
            queue_1[q_1_index].response_time = time;
            queue_1[q_1_index].response_time_flag = true;
        }

        if ((time + queue_1[q_1_index].remaining_time) <= x){
            printf("\n   Process(PID : %d)  run for %d" ,queue_1[q_1_index].p_id, queue_1[q_1_index].remaining_time);
            time += queue_1[q_1_index].remaining_time;
            queue_1[q_1_index].remaining_time = 0;
            queue_1[q_1_index].completion_time = time;
            q_1_index ++;
        }
        else if (x-time != 0){
            printf("\n   Process(PID : %d)  run for %d" ,queue_1[q_1_index].p_id, x-time);
            queue_1[q_1_index].remaining_time -= (x-time);
            time = x;
            break;
        }
        else{
            break;
        }
    }

}

void print_table(){
    printf("\n\n====  Round Robin Algorithm :");
    printf("\nPId\t     Priority\t     Burst Time\t     Waiting Time\t   TurnAround Time\t     Response Time");
    int total_response_time;

    total_response_time = 0;
    for(int i=0; i<q_3_count; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d", queue_3[i].p_id, queue_3[i].priority,
                queue_3[i].burst_time, queue_3[i].completion_time - queue_3[i].arrival_time - queue_3[i].burst_time,
                queue_3[i].completion_time - queue_3[i].arrival_time, queue_3[i].response_time);
        total_response_time += queue_3[i].response_time;
    }
    printf("\n\nAverage response time : %.2f", (float)total_response_time/(float)q_3_count);

    printf("\n\n====  Priority Queue Algorithm :");
    printf("\nPId\t     Priority\t     Burst Time\t     Waiting Time\t   TurnAround Time\t     Response Time");

    total_response_time = 0;
    for(int i=0; i<q_2_count; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d", queue_2[i].p_id, queue_2[i].priority,
                queue_2[i].burst_time, queue_2[i].completion_time - queue_2[i].arrival_time - queue_2[i].burst_time,
                queue_2[i].completion_time - queue_3[i].arrival_time, queue_2[i].response_time);
        total_response_time += queue_2[i].response_time;
    }
    printf("\n\nAverage response time : %.2f", (float)total_response_time/(float)q_2_count);

    printf("\n\n===  FCFS Algorithm : ");
    printf("\nPId\t     Priority\t     Burst Time\t     Waiting Time\t   TurnAround Time\t     Response Time");

    total_response_time = 0;
    for(int i=0; i<q_1_count; i++){
        printf("\n%d\t\t%d\t\t%d\t\t%d\t\t\t%d\t\t\t%d", queue_1[i].p_id, queue_1[i].priority,
                queue_1[i].burst_time, queue_1[i].completion_time - queue_1[i].arrival_time - queue_1[i].burst_time,
                queue_1[i].completion_time - queue_1[i].arrival_time, queue_1[i].response_time);
        total_response_time += queue_1[i].response_time;
    }
    printf("\n\nAverage response time : %.2f", (float)total_response_time/(float)q_1_count);
}

void scheduling(){
    int x = 0;

    qsort(queue_3, q_3_count, sizeof(struct process), comp_arrival_time);
    qsort(queue_2, q_2_count, sizeof(struct process), comp_priority);
    qsort(queue_1, q_1_count, sizeof(struct process), comp_arrival_time);

    while(true) {
        if (round_robin_flag != q_3_count){
            printf("\n\nQueue 1 running [high] .....");
            round_robin();
            x++;
        }

        if (q_2_index < q_2_count){
            printf("\n\nQueue 2 running[medium] .....");
            priority();
            x++;
        }

        if (q_1_index < q_1_count){
            printf("\n\nQueue 3 running[low] .....");
            fcfs();
            x++;
        }

        if (x == 0){
            printf("\n\n===> Execution complete");
            break;
        }
        x = 0;

    }
    print_table();
}


int main() {
    int n;
    printf("###########   Multilevel Queue Scheduling Algorithm   #############\n");

// ---------------------------------------------------------------------------------------------------------------------

//    int process_array[][4] = {
//            {100, 10, 2},            // format : {process_ID, burst_time, priority}
//            {101, 10, 1},           // priority range :  1-10  (lowest : 1-4, medium : 5-7, highest : 8-10)
//            {102, 10, 7},
//            {105, 10, 5},
//            {103, 9, 8},
//            {106, 8, 9},
//            {107, 10, 8},
//            // add new process here :
//
//
//    };


// ---------------------------------------------------------------------------------------------------------------------

    printf("\nEnter number of process : ");
    scanf("%d", &n);
    int process_array[n][4];

    for (int i=0; i<n; i++){
        printf("\nProcess %d : ", i+1);
        printf("\nProcess ID : ");
        scanf("%d", &process_array[i][0]);
        printf("\nBurst Time : ");
        scanf("%d", &process_array[i][1]);
        printf("\nPriority[1-9]:");
        scanf("%d", &process_array[i][2]);
    }



// ---------------------------------------------------------------------------------------------------------------------

    n = sizeof(process_array) / sizeof(process_array[1]);

    for (int i=0; i<n; i++){
        struct process p;
        p.p_id = process_array[i][0];
        p.burst_time = process_array[i][1];
        p.priority = process_array[i][2];
        p.arrival_time = 0;
        p.remaining_time = p.burst_time;
        p.response_time_flag = false;

        if (p.priority <= 4){
            queue_1[q_1_count] = p;
            q_1_count ++;
        }
        else if (p.priority <= 7){
            queue_2[q_2_count] = p;
            q_2_count ++;
        }
        else{
            queue_3[q_3_count] = p;
            q_3_count ++;
        }
    }

    scheduling();

    return 0;
}


