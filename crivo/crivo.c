#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int *prime_list;
int prime_list_len;

void crivo (int n){
    int i, j;
    int s;

    s = (int) sqrt(n) + 1;
    prime_list = (int *) malloc (s * sizeof(int));
    for (i = 0; i < s; i++){
        if(i < 2) prime_list[i] = 0;
        else{
            prime_list[i] = i;
            j = 2;
            while(j * j <= i){
                if (i % j == 0){
                    prime_list[i] = 0;
                    break;
                }
                j++;
            }
        }
    }
    i = 0;
    for(j = 0; j < s; j++){
        if(prime_list[j]){
            prime_list[i++] = prime_list[j];
        }
    }
    prime_list_len = i;
    prime_list[prime_list_len] = n;
}

int eh_primo(int p){
    int i;
    if(p < 2) return 0;
    i = 0;
    while(prime_list[i] * prime_list[i] <= p){
        if(p % prime_list[i] == 0) return 0;
        i++;
    }
    return 1;
}

int main (){
	int *a;
	int count;
	int i;
	int n;
    clock_t t1, t2;

	scanf("%i", &n);

	crivo(n);
	a = (int *) malloc (n * sizeof(int));
	t1 = clock();

	for (i = 0; i < n; i++){
	    a[i] = eh_primo(i);
	}

    t2 = clock() - t1;
	for (i = 0;i < n; i++){
	    count += a[i];
	}
	printf("Existem %d numeros primos menores que %d\n", count, n);
	printf("O programa demorou %.2f segundos", ((float)t2)/CLOCKS_PER_SEC);
	free(a);
	free(prime_list);
	return 0;
}
