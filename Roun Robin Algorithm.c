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
