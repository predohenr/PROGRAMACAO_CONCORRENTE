#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
#include <math.h>

void crivo_mpi(int numElementos,int numElem_por_processo,int rank, int numProcessos){
    double inicio,fim;
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0){
        inicio = MPI_Wtime();
    }
    char *ehPrimo = (char*)malloc((numElem_por_processo)*sizeof(char));
    const int numElementosSqrt = (int)sqrt((double)numElementos);

    for (int i = 0; i < numElem_por_processo; i++){
        ehPrimo[i] = 1;
    }

    int n;
    if (rank == 0){
		n = 2;
    }

    int primo = 2;
    int primeiro,limiteInf;
    limiteInf = rank*numElem_por_processo;
    do{
        if (primo * primo > limiteInf){
			primeiro = primo * primo - limiteInf;
		}
		else{
			if (!(limiteInf % primo)){
				primeiro = 0;
            }
			else{
				primeiro = primo - (limiteInf % primo);
            }
		}
        for (int i = primeiro; i < numElem_por_processo; i += primo){
			ehPrimo[i] = 0;
        }
        if (rank == 0){
            while (ehPrimo[++n]==0);
            primo = n;
		}
        MPI_Bcast(&primo, 1, MPI_INT, 0, MPI_COMM_WORLD);
    } while (primo*primo<=numElementos);

    int contador = 0;
    int total;
    for (int i = 0; i <numElem_por_processo; i++){
        contador += ehPrimo[i];
    }

    MPI_Reduce(&contador, &total, 1, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    if (rank==0){
        fim = MPI_Wtime();
    }
    if (rank==0){
        printf("Total de primos: %d\n",total-2);
        printf("Tempo: %f\n",fim-inicio);
    }
    free(ehPrimo);
}

int main(){

    int numElementos = ;
    MPI_Init(NULL, NULL);
    int numProcessos;
    MPI_Comm_size(MPI_COMM_WORLD, &numProcessos);
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char nomeProcessos[MPI_MAX_PROCESSOR_NAME];
    int name_len;
    MPI_Get_processor_name(nomeProcessos, &name_len);

    int numElem_por_processo = (int)(numElementos/numProcessos);
    if (numElementos%numElem_por_processo!=0){
        MPI_Abort(MPI_COMM_WORLD,1);
    }

    crivo_mpi(numElementos,numElem_por_processo,rank,numProcessos);

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Finalize();
    return 0;
}
