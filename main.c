/*
 * * --- IDENTIFICAÇÃO DO GRUPO --- 
 * Integrante 1: Enrique Cipolla Martins, RA: [Numero do RA]
 * Integrante 2: Henrique Ferreira Marciano, RA: 10439797
 * ...
 * * --- REFERÊNCIAS --- 
 * https://stackoverflow.com/questions
 * https://pt.stackoverflow.com/questions/587661/arquivos-linguagem-c
 * https://www.tutorialspoint.com/c_standard_library/limits_h.htm
 * * --- LINK DO VÍDEO --- 
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h> //Para usar INT_MAX como "infinito"

#define MAX_ESQUINAS 100 //Limite de esquinas

//Declaração das funções 
void lerDadosEntrada(const char* nomeArquivo, int* esquinaIncendio, int* numEsquinas, int mapa[][MAX_ESQUINAS + 1]);
void executarRotaMaisRapida(int numEsquinas, int mapa[][MAX_ESQUINAS + 1], int T[], int R[]);
void gerarSaida(int esquinaIncendio, int numEsquinas, int T[], int R[]);
void reconstruirCaminho(int esquinaAtual, int R[], FILE* arquivo);

//Main
int main() {
    
    //Variáveis Principais
    int esquinaIncendio;
    int numEsquinas;
    
    //Matriz de adjacência para o mapa. mapa[origem][destino] = tempo
    //+1 pois as esquinas são 1-indexadas 
    int mapa[MAX_ESQUINAS + 1][MAX_ESQUINAS + 1];

    //Vetores do algoritmo
    int T[MAX_ESQUINAS + 1]; // T[]: Tempos mínimos
    int R[MAX_ESQUINAS + 1]; // R[]: Rota (predecessores)

    //Carregar Dados
    lerDadosEntrada("entrada.txt", &esquinaIncendio, &numEsquinas, mapa);
    printf("Dados carregados de 'entrada.txt'.\n");

    //Executar Algoritmo
    executarRotaMaisRapida(numEsquinas, mapa, T, R);
    printf("Algoritmo da rota mais rapida executado.\n");

    //Gerar Saída
    gerarSaida(esquinaIncendio, numEsquinas, T, R);
    printf("Saida gerada em 'saida.txt' e no console.\n");

    return 0;
}


//Ler o arquivo texto e popular as variáveis e a matriz do mapa.
void lerDadosEntrada(const char* nomeArquivo, int* esquinaIncendio, int* numEsquinas, int mapa[][MAX_ESQUINAS + 1]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    //Validação da abertura do arquivo
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo '%s'!\n", nomeArquivo);
        exit(1); //Para o programa se o arquivo não for encontrado
    }

    //Leitura dos dados iniciais
    fscanf(arquivo, "%d", esquinaIncendio);
    fscanf(arquivo, "%d", numEsquinas);

    //Validação para checar se excede o limite 
    if (*numEsquinas > MAX_ESQUINAS) {
        printf("O numero de esquinas (%d) excede o limite do programa (%d).\n", *numEsquinas, MAX_ESQUINAS);
        fclose(arquivo);
        exit(1);
    }

    //Inicialização do mapa (começando em 1)
    for (int i = 1; i <= *numEsquinas; i++) {
        for (int j = 1; j <= *numEsquinas; j++) {
            mapa[i][j] = -1; // -1 = sem rota direta
        }
    }

    int origem, destino, tempo;

    //Loop de leitura das triplas
    while (fscanf(arquivo, "%d", &origem) == 1) {
        
        //Condição de parada: linha com um único 0
        if (origem == 0) {
            break;
        }

        //Se não for 0, lê o resto da tripla
        if (fscanf(arquivo, "%d %d", &destino, &tempo) != 2) {
             printf("Formato de arquivo invalido durante a leitura das ruas.\n");
             break;
        }
        
        mapa[origem][destino] = tempo;
    }

    fclose(arquivo);
}

//Executa o algoritmo (Dijkstra) e preenche T[] e R[].
void executarRotaMaisRapida(int numEsquinas, int mapa[][MAX_ESQUINAS + 1], int T[], int R[]) {
    int E[MAX_ESQUINAS + 1]; //Estrutura auxiliar E

    //Inicialização
    for (int i = 1; i <= numEsquinas; i++){
        T[i] = INT_MAX; //T[e] <- infinito [cite: 20]
        E[i] = 1; //Adiciona 'i' ao conjunto E [cite: 18]
        R[i] = -1; //-1 significa "sem predecessor"
    }

    T[1] = 0; //Tempo para o quartel (esquina 1) é 0

    // "enquanto E não estiver vazio"
    // (Uma implementação simples de Dijkstra itera N vezes)
    for (int count = 1; count <= numEsquinas; count++){
        
        int v = -1;
        int menorTempo = INT_MAX;

        //v <- uma esquina em E com menor custo no vetor T[]
        for (int i = 1; i <= numEsquinas; i++){
            //se i esta em E e tem o menor tempo
            if(E[i] == 1 && T[i] < menorTempo){
                menorTempo = T[i];
                v = i;
            }
        }

        //Se v == -1, significa que o resto do grafo é inalcançável
        if (v == -1){
            break;
        }

        E[v] = 0; //"E <- E - {v}" (remove v de E)

        //para cada esquina e que seja acessada a partir da esquina v
        for (int e = 1; e <= numEsquinas; e++){
            
            //tal que a esquina e esteja presente em E
            //mapa[v][e] != -1 -> checa se há caminho (acessada a partir de v)
            //E[e] == 1 -> checa se 'e' está em E
            //T[v] != INT_MAX -> checa se 'v' é alcançável
            if(mapa[v][e] != -1 && E[e] == 1 && T[v] != INT_MAX){
                
                int novoTempo = T[v] + mapa[v][e]; //T[v] + tempo para ir de v até e
                
                //se T[e] > T[v] + tempo par ir de v até e
                if(novoTempo < T[e]){
                    T[e] = novoTempo; //Atualiza o tempo
                    
                    // Armazena a rota (R[])
                    R[e] = v;
                }
            }
        }
    }
}

//Usa R[] para imprimir o caminho de forma recursiva
void reconstruirCaminho(int esquinaAtual, int R[], FILE* arquivo) {
    // Caso base: chegamos ao quartel (esquina 1)
    if (esquinaAtual == 1) {
        fprintf(arquivo, "1");
    } else if (R[esquinaAtual] == -1) {
        //Segurança: caso o caminho não exista e T[] não foi checado
        fprintf(arquivo, "(rota invalida)");
    } else {
        //Chamada recursiva para o predecessor
        reconstruirCaminho(R[esquinaAtual], R, arquivo);
        //Imprime a esquina atual após o caminho anterior
        fprintf(arquivo, " %d", esquinaAtual);
    }
}

//Imprime no console e salva em "saida.txt"
void gerarSaida(int esquinaIncendio, int numEsquinas, int T[], int R[]) {
    
    FILE* arquivo_saida = fopen("saida.txt", "w");
    if (arquivo_saida == NULL) {
        printf("Erro ao criar o arquivo de saída 'saida.txt'!\n");
        return;
    }

    //Checa se a esquina do incêndio é alcançável
    if (T[esquinaIncendio] == INT_MAX) {
        const char* msg = "Nao foi encontrada uma rota ate a esquina do incendio.\n";
        
        //Imprime na tela
        printf("%s", msg);
        //Salva no arquivo
        fprintf(arquivo_saida, "%s", msg);

    } else {
        //Saída na Tela com stdout
        printf("Rota até a esquina #%d: ", esquinaIncendio);
        reconstruirCaminho(esquinaIncendio, R, stdout); //stdout é o "arquivo" do console
        printf("\n");
        printf("Tempo calculado para rota = %d min.\n", T[esquinaIncendio]);

        //Saída no Arquivo saida.txt
        fprintf(arquivo_saida, "Rota até a esquina #%d: ", esquinaIncendio);
        reconstruirCaminho(esquinaIncendio, R, arquivo_saida);
        fprintf(arquivo_saida, "\n");
        fprintf(arquivo_saida, "Tempo calculado para rota = %d min.\n", T[esquinaIncendio]);
    }

    //Fecha o arquivo
    fclose(arquivo_saida);
}
