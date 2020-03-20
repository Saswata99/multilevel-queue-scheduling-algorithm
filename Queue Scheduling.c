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