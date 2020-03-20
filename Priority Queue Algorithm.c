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
