/*
 * Universidade Presbiteriana Mackenzie
 * Projeto e Análise de Algoritmos II - 2024
 * * PROJETO 2: Bombeiros
 * * --- IDENTIFICAÇÃO DO GRUPO --- 
 * Integrante 1: [Nome Completo], RA: [Numero do RA]
 * Integrante 2: [Nome Completo], RA: [Numero do RA]
 * ...
 * * --- REFERÊNCIAS --- 
 * (ex: Livro, Artigo, Site, etc.)
 * * --- LINK DO VÍDEO --- 
 * (Colocar o link do YouTube aqui no Dia 25)
 * * --- LINKS CHATGPT (ou similar) --- 
 * (Colocar links de compartilhamento, se usar)
 */

#include <stdio.h>    // Para printf, scanf, fopen, fclose, fprintf
#include <stdlib.h>   // Para exit (se houver erro de arquivo)
#include <limits.h>   // Para usar INT_MAX como "infinito" 

#define MAX_ESQUINAS 100 // Um limite razoável, pode ajustar se necessário

// --- DECLARAÇÃO DAS FUNÇÕES AUXILIARES --- 
// (Vamos declarar as funções que planejamos criar)

void lerDadosEntrada(const char* nomeArquivo, int* esquinaIncendio, int* numEsquinas, int mapa[][MAX_ESQUINAS + 1]);
void executarRotaMaisRapida(int numEsquinas, int mapa[][MAX_ESQUINAS + 1], int T[], int R[]);
void gerarSaida(int esquinaIncendio, int numEsquinas, int T[], int R[]);
void reconstruirCaminho(int esquinaAtual, int R[], FILE* arquivo);

// --- FUNÇÃO PRINCIPAL ---
int main() {
    
    // --- Variáveis Principais ---
    int esquinaIncendio;
    int numEsquinas;
    
    // Matriz de adjacência para o mapa. mapa[origem][destino] = tempo
    // +1 pois as esquinas são 1-indexadas 
    int mapa[MAX_ESQUINAS + 1][MAX_ESQUINAS + 1];

    // Vetores do algoritmo [cite: 15]
    int T[MAX_ESQUINAS + 1]; // T[]: Tempos mínimos
    int R[MAX_ESQUINAS + 1]; // R[]: Rota (predecessores)

    // --- Etapa 1: Carregar Dados ---
    // (Implementar nos Dias 2-5)
    // lerDadosEntrada("entrada.txt", &esquinaIncendio, &numEsquinas, mapa);
    printf("Etapa 1: Ler dados (Ainda não implementado)\n");

    // --- Etapa 2: Executar Algoritmo ---
    // (Implementar nos Dias 8-12)
    // executarRotaMaisRapida(numEsquinas, mapa, T, R);
    printf("Etapa 2: Executar algoritmo (Ainda não implementado)\n");

    // --- Etapa 3: Gerar Saída ---
    // (Implementar nos Dias 15-19)
    // gerarSaida(esquinaIncendio, numEsquinas, T, R);
    printf("Etapa 3: Gerar saída (Ainda não implementado)\n");

    printf("\nProjeto iniciado! Próximo passo: Implementar lerDadosEntrada.\n");

    return 0;
}


// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

/*
 * Função: lerDadosEntrada
 * (Implementar nos Dias 2-5)
 * Objetivo: Ler o arquivo texto e popular as variáveis e a matriz do mapa.
 */
void lerDadosEntrada(const char* nomeArquivo, int* esquinaIncendio, int* numEsquinas, int mapa[][MAX_ESQUINAS + 1]) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo de entrada '%s'!\n", nomeArquivo);
    }
    fscanf(arquivo, "%d", esquinaIncendio);

    fscanf(arquivo, "%d", numEsquinas);


    for (int i = 0; i <= *numEsquinas; i++) {
        for (int j = 0; j <= *numEsquinas; j++) {
            mapa[i][j] = -1; // -1 = sem rota direta
        }
    }

    int origem, destino, tempo;

    while (fscanf(arquivo, "%d %d %d", &origem, &destino, &tempo) == 3) {
        if (origem == 0) {
            break;
        }
        mapa[origem][destino] = tempo;
    }

    fclose(arquivo);
}

/*
 * Função: executarRotaMaisRapida
 * (Implementar nos Dias 8-12)
 * Objetivo: Executar o algoritmo (Dijkstra) e preencher T[] e R[].
 */
void executarRotaMaisRapida(int numEsquinas, int mapa[][MAX_ESQUINAS + 1], int T[], int R[]) {
    int E[MAX_ESQUINAS + 1];

    for (int i = 1; i <= numEsquinas; i++){
        T[i] = INT_MAX; //Infinito
        E[i] = 1; //Todas as esquinas começam com E
        R[i] = -1; // -1 significa "sem predecessor"
    }

    T[1] = 0;

    //Enquanto E não estiver vazio, iterar numEsquinas
    for (int count = 1; count <= numEsquinas; count++){
        
        int v = -1;
        int menorTempo = INT_MAX;

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

        E[v] = 0;

        //loop 'para cada vizinho e' de 'v'
        for (int e = 1; e <= numEsquinas; e++){
            if(mapa[v][e] != -1 && E[e] == 1 && T[v] != INT_MAX){
                //checa se existe um caminho de 'v' para 'e', se esquina 'e' ainda está em E (E[e] == 1) e se T[v] não é infinito
                int novoTempo = T[v] + mapa[v][e];
                
                if(novoTempo < T[e]){
                    T[e] = novoTempo;
                    //salva v como predescessor de e no caminho mais curto
                    R[e] = v;
                }
            }
        }
    }
}

/*
 * Função: gerarSaida
 * (Implementar nos Dias 15-19)
 * Objetivo: Imprimir no console e salvar em "saida.txt" 
 */
void gerarSaida(int esquinaIncendio, int numEsquinas, int T[], int R[]) {
    // 1. Abrir "saida.txt" (fopen)
    // 2. Chamar reconstruirCaminho(esquinaIncendio, R, stdout);
    // 3. Chamar reconstruirCaminho(esquinaIncendio, R, arquivo_saida);
    // 4. Imprimir tempo total no console (printf) 
    // 5. Imprimir tempo total no arquivo (fprintf)
    // 6. Fechar arquivo (fclose)
}

/*
 * Função: reconstruirCaminho
 * (Implementar nos Dias 15-17)
 * Objetivo: Usar R[] para imprimir o caminho (do início ao fim).
 */
void reconstruirCaminho(int esquinaAtual, int R[], FILE* arquivo) {
    // Esta função é um pouco mais complexa, pois R[] dá o caminho ao contrário.
    // Pode ser feita com recursão ou salvando em um array e imprimindo ao contrário.
    
    // Exemplo com recursão (mais elegante):
    // if (esquinaAtual == 1) {
    //    fprintf(arquivo, "1");
    // } else {
    //    reconstruirCaminho(R[esquinaAtual], R, arquivo);
    //    fprintf(arquivo, " %d", esquinaAtual);
    // }
}
