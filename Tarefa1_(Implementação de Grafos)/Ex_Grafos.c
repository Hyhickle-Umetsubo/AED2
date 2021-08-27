/*//------------------------------------------------------------------------------------------------------------------------------------------------------------------ 
Hyhickle Ryozo Umetsubo Gonçalves - AED2 (Exercício Grafos)
Condição 1 - Implementar um programa na linguagem de sua escolha, que permita a representação em memória de um grafo.
Condição 2 - Este programa deve permitir a entrada dos vértices e os pesos das arestas.
Condição 3 - Permitir o armazenamento de até 20 vértices
Condição 4 - Fazer a leitura dos pesos das arestas de cada vértice
Condição 5 - Considerar sempre vértices positivos
Condição 6 - Mostrar os dados armazenados
*/
//--------------------------------------------------------------------------------------------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Funções Usadas ao longo do Programa
void menu_inicial();
void incluir_vertice();
void listar_vertice();
void gerar_matriz();

//Buffers do Programa onde ficam todas as variaveis e os vertices
void *buffer_variaveis;
void *buffer_vertices;

typedef struct variaveis
{
    int numero_vertices;
    int escolha_menu;
    int contador;
    int contador2;
    int aux;
    int aux_peso;
    int linha;
    int coluna;
    int numero_ligacoes;
} Variaveis;

typedef struct vertices
{
    char vertice[20];
} Vertices;

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que Adiciona Arestas, Pesos e Imprime Matriz
void gerar_matriz()
{
    Variaveis *a;
    a = buffer_variaveis;

    int matriz[a->numero_vertices][a->numero_vertices];

    //Esse laço faz com que a matriz seja preenchida inicialmente com zeros
    for (a->linha = 0; a->linha < a->numero_vertices; a->linha++)
    {
        for (a->coluna = 0; a->coluna < a->numero_vertices; a->coluna++)
        {
            matriz[a->linha][a->coluna] = 0;
        }
    }

    for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
    {
        do
        {
            printf("\nO item '%d' tem quantas ligacoes: ", a->contador + 1);
            scanf("%d", &a->numero_ligacoes);
            if (a->numero_ligacoes > a->numero_vertices)
            {
                printf("\nINVALIDO - Numero de Ligacoes maior que a Quantidade de Vertices\n");
            }
        } while (a->numero_ligacoes > a->numero_vertices);

        for (a->contador2 = 0; a->contador2 < a->numero_ligacoes; a->contador2++)
        {
            do
            {
                printf("Tem ligacao com: ");
                scanf("%d", &a->aux);
                if ((a->aux > a->numero_vertices) || (a->aux == 0))
                {
                    printf("\nINVALIDO - Ligacao com Vertice Inexistente\n");
                }
                else
                {
                    if (((matriz[a->contador][a->aux - 1]) && (matriz[a->aux - 1][a->contador])) != 0)
                    {
                        printf("\nEssa aresta ja existia, e sera alterada pelo novo peso\n");
                    }
                }
            } while ((a->aux > a->numero_vertices) || (a->aux == 0));
            printf("Qual o peso da Aresta: ");
            scanf("%d", &a->aux_peso);
            matriz[a->contador][a->aux - 1] = a->aux_peso;
            matriz[a->aux - 1][a->contador] = a->aux_peso;
        }
    }
    printf("\n\n");
    listar_vertice();

    printf("-----MATRIZ DE ADJACENCIA-----\n\n");
    //Laços para imprimir as Matrizes de forma Organizada
    printf("\t%d", 1);
    for (a->contador = 1; a->contador < a->coluna; a->contador += 1)
    {
        printf("\t%d", a->contador + 1);
    }
    printf("\n");

    printf("   ");
    for (a->contador = 0; a->contador < 10 * a->coluna; a->contador += 1)
    {
        printf("-");
    }
    printf("\n");

    for (a->linha = 0; a->linha < a->numero_vertices; a->linha++)
    {
        printf("%2d|", a->linha + 1);
        for (a->coluna = 0; a->coluna < a->numero_vertices; a->coluna++)
        {
            printf("\t%d", matriz[a->linha][a->coluna]);
        }
        printf("\n");
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que adiciona Vertices
void incluir_vertice()
{
    Variaveis *a;
    a = buffer_variaveis;
    Vertices *v;
    buffer_vertices = (Vertices *)realloc(buffer_vertices, (sizeof(Vertices) * (a->numero_vertices + 1)));
    if (buffer_vertices == NULL)
    {
        printf("\n---Erro, falta de memoria---\n");
        exit(1);
    }
    v = buffer_vertices + (sizeof(Vertices) * (a->numero_vertices));
    printf("\nInsira o nome do Vertice: ");
    scanf("%s", v->vertice);

    printf("-----VERTICE ADICIONADO COM SUCESSO-----\n");
    a->numero_vertices++;
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que lista todos os Vertices
void listar_vertice()
{
    Variaveis *a;
    Vertices *v;
    a = buffer_variaveis;
    v = buffer_vertices;
    printf("\n-----VERTICES INSERIDOS-----\n");
    for (a->contador = 0; a->contador < a->numero_vertices; a->contador++)
    {
        printf("\n%d - %s ", a->contador + 1, v->vertice);
        v++;
    }
    printf("\n\n");
    return;
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
//Função que chama o menu do programa
void menu_inicial()
{
    Variaveis *a;
    a = buffer_variaveis;
    for (;;)
    {
        printf("\n\nDeseja inserir algum vertice: \n");
        printf("1-Sim\n");
        printf("2-Nao\n");
        printf("Digite sua Escolha: ");
        scanf("%d", &a->escolha_menu);

        switch (a->escolha_menu)
        {
        case 1:
            incluir_vertice();
            break;
        case 2:
            printf("\n\nO que deseja fazer agora: \n");
            printf("1-Adicionar Pesos nas Arestas e imprimir a Matriz de Adjacencia\n");
            printf("2-Finalizar o Programa\n");
            printf("Digite sua Escolha: ");
            scanf("%d", &a->escolha_menu);
            if (a->escolha_menu == 1)
            {
                listar_vertice();
                gerar_matriz();
            }
            if (a->escolha_menu == 2)
            {
                free(buffer_variaveis);
                free(buffer_vertices);
                return;
            }
            break;
        default:
            printf("Opcao Invalida");
            break;
        }
    }
}

//------------------------------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    Variaveis *a;
    buffer_variaveis = malloc(sizeof(Variaveis));
    if (buffer_variaveis == NULL)
    {
        printf("Erro");
        exit(1);
    }
    a = buffer_variaveis;
    a->numero_vertices = 0;
    menu_inicial();
}
