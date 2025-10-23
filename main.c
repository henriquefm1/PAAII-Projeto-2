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
    // 1. Abrir o arquivo (fopen)
    // 2. Tratar erro se o arquivo não existir
    // 3. Ler esquinaIncendio (fscanf)
    // 4. Ler numEsquinas (fscanf)
    // 5. Inicializar o 'mapa' (ex: com 0 ou -1)
    // 6. Ler as triplas (origem, destino, tempo) em um loop (fscanf)
    // 7. Parar o loop quando origem for 0 
    // 8. Fechar o arquivo (fclose)
}

/*
 * Função: executarRotaMaisRapida
 * (Implementar nos Dias 8-12)
 * Objetivo: Executar o algoritmo (Dijkstra) e preencher T[] e R[].
 */
void executarRotaMaisRapida(int numEsquinas, int mapa[][MAX_ESQUINAS + 1], int T[], int R[]) {
    // 1. Criar vetor E[] (visitados/na fila) 
    // 2. Inicializar T[] com INT_MAX, E[] com 1 (presente), R[] com -1 (nulo) [cite: 19, 20]
    // 3. T[1] = 0 
    // 4. Loop 'enquanto E não estiver vazio' 
    // 5.   Achar 'v' em E com menor T[v] 
    // 6.   Remover 'v' de E (E[v] = 0) 
    // 7.   Loop 'para cada vizinho e' de 'v' [cite: 26]
    // 8.     Se (T[e] > T[v] + mapa[v][e]) E 'e' está em E [cite: 27, 28]
    // 9.       T[e] = T[v] + mapa[v][e] 
    // 10.      R[e] = v  <- ESTA É A MODIFICAÇÃO CHAVE! 
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
