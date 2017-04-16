#include <mpi.h>
#include <stdio.h>
#include <unistd.h>

#define COUNT 64

int main(int argc, char *argv[]){
    // Initialize the MPI environment
    MPI_Init(&argc, &argv);

    // Get the number of processes
    int world_size;
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    // Get the rank of the processes
    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    printf("world_rank: %d\n", world_rank);

    // Get the name of the processor
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(processor_name, &name_len);

    char name[COUNT] = {0};
    MPI_Status status;
    // Print off a hello world message
    if (world_rank == 0) {
            printf("Hello MPI from the server process!\n");

            for (int worker_idx=1; worker_idx<world_size; worker_idx++) {
                    MPI_Recv(name, COUNT, MPI_CHAR, worker_idx, 999, MPI_COMM_WORLD, &status);
                    printf("Hello MPI!\n");
                    printf(" message from %d of %d on %s\n", worker_idx, world_size, name);
            }
    } else {
            gethostname(name, sizeof(name));
            MPI_Send(name, COUNT, MPI_CHAR, 0, 999, MPI_COMM_WORLD);
    }

    // Finalize the MPI environment;
    MPI_Finalize();

    return 0;
}
