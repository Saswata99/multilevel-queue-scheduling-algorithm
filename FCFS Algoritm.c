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