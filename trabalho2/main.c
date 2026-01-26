#include <stdio.h>
#include <stdlib.h>

#include "trabalho2.h"
#include "trabalho2.c"

int menu();

// void dobrar(int *x);

int menu()
{
    int op;
    printf("Digite as opção desejada\n");
    printf("0 - Sair\n");
    printf("1 - Inserir\n");
    printf("2 - Excluir número específico\n");
    printf("3 - Listar uma estrutura\n");
    printf("4 - Dobrar Numero\n");
    printf("5 - Criar estrutura auxiliar\n");
    printf("6 - excluir número do final da estrutura\n");
    printf("7- Conseguir dados ordenados da estrutura \n");
    printf("8 - Conseguir dados de todas as estruturas \n");
    printf("9 - Conseguir dados ordenados de todas as estruturas \n");
    printf("10 - Modificar tamanho da estrutura");
    scanf("%d", &op);
    return op;
}

int main()
{
    inicializar();

    int op;
    int sair = 0;
    int ret;

    while (!sair)
    {
        op = menu();
        switch (op)
        {
        case 0:
        {
            sair = 1;
            finalizar();
            break;
        }
        case 1:
        { // inserir
            // TODO
            int posicao, valor;

            printf("Qual a estrutura a ser inserida um valor e qual é esse valor? (Posições variam de 1 a 10)?");
            scanf("%d %d", &posicao, &valor);

            ret = inserirNumeroEmEstrutura(posicao, valor);
            if (ret == SUCESSO)
            {
                printf("Inserido com sucesso");
            }
            else if (ret == SEM_ESPACO)
            {
                printf("Sem Espaço");
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura Auxiliar");
            }
            break;
        }

        case 2:
        { // excluir
          // TODO
            int posicao, num;
            printf("Estrutura e número a ser excluído \n");
            scanf("%d %d", &posicao, &num);

            int retorno = excluirNumeroEspecificoDeEstrutura(posicao, num);

            if (retorno == POSICAO_INVALIDA)
            {
                printf("Posição inválida \n");
            }
            else if (retorno == NUMERO_INEXISTENTE)
            {
                printf("O número não existe \n");
            }
            else if (retorno == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Estrutura auxiliar vazia \n");
            }
            else if (retorno == SUCESSO)
            {
                printf("Número excluído com sucesso \n");
            }
            break;
        }

        case 3:
        { // recuperar dados estrutura auxiliar
            int posicao, retorno;
            printf("Qual a estrutura a ser listada (1..10)?");
            scanf("%d", &posicao);

            int qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

            if (qtd == POSICAO_INVALIDA)
            {
                printf("Posição inválida\n");
                break;
            }
            if (qtd == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura auxiliar\n");
                break;
            }
            if (qtd == ESTRUTURA_AUXILIAR_VAZIA)
            {
                printf("Estrutura auxiliar vazia\n");
                break;
            }
            else
            { // existe elemento
                int vetorAux[qtd];

                retorno = getDadosEstruturaAuxiliar(posicao, vetorAux);

                if (retorno == SUCESSO)
                {
                    // imprimir para os dados para o usuário
                    int i = 0;
                    for (; i < qtd; i++)
                    {
                        printf("%d \n", vetorAux[i]);
                    }
                }
                else if (retorno == POSICAO_INVALIDA)
                {
                    printf("A Posição é inválida");
                }
                else if (retorno == SEM_ESTRUTURA_AUXILIAR)
                {
                    printf("Não há estrutura auxiliar");
                }
            }
            break;
        }

        case 4:
        { // dobrar
            // ler um numero
            int valor;
            scanf("%i", &valor);

            dobrar(&valor);

            // passar para um funcao (void dobrar(...)) que recebe o numero e dobra (EstruturaVetores.c)

            printf("%i", valor);

            break;
        }

        case 5:
            int posicao, tamanho;
            printf("Qual a posição que deve ser criada a estrutura? E qual o seu tamanho: (Posicoes variam de 1 a 10)?");
            scanf("%d %d", &posicao, &tamanho);

            int ret = criarEstruturaAuxiliar(posicao, tamanho);

            if (ret == JA_TEM_ESTRUTURA_AUXILIAR)
            {
                printf("Já existe uma estrutura auxiliar nessa posição! ");
            }
            else if (ret == SEM_ESPACO_DE_MEMORIA)
            {
                printf("Não foi possível criar a estrutura, devido à falta de memória ");
            }
            else if (ret == POSICAO_INVALIDA)
            {
                printf("A posição é inválida! ");
            }
            else if (ret == TAMANHO_INVALIDO)
            {
                printf("O tamanho não pode ser menor que 1!");
            }
            else if (ret == SUCESSO)
            {
                printf("Estrutura criada com sucesso!");
            }

            break;

        case 6:

            printf("Posição \n");
            scanf("%d", &posicao);

            ret = excluirNumeroDoFinaldaEstrutura(posicao);

            if (ret == SUCESSO)
            {
                printf("Sucesso \n");
                break;
            }
            else if (ret == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura \n");
                break;
            }
            else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
            {
                printf("Estrutura vazia \n");
                break;
            }
            else if (ret == POSICAO_INVALIDA)
            {
                printf("Posição inválida \n");
                break;
            }

        case 7:

            int qtd;
            
            printf("Posição \n");
            scanf("%d", posicao);

            qtd = getQuantidadeElementosEstruturaAuxiliar(posicao);

            if (qtd == POSICAO_INVALIDA)
            {
                printf("Posição inválida\n");
                break;
            }
            if (qtd == SEM_ESTRUTURA_AUXILIAR)
            {
                printf("Sem estrutura auxiliar\n");
                break;
            }
            if (qtd == ESTRUTURA_AUXILIAR_VAZIA)
            {
                printf("Estrutura auxiliar vazia\n");
                break;
            }
            else
            { // existe elemento
                int vetorAux[qtd];

                int ret = getDadosOrdenadosEstruturaAuxiliar(posicao, vetorAux);

                if (ret == SUCESSO)
                {
                    for (int i = 0; i < qtd; i++)
                    {
                        printf("%d \n", vetorAux[i]);
                    }

                    break;
                    
                }
                else if (ret == SEM_ESTRUTURA_AUXILIAR)
                {
                    printf("Sem estrutura \n");
                    break;
                }
                else if (ret == ESTRUTURA_AUXILIAR_VAZIA)
                {
                    printf("Estrutura vazia \n");
                    break;
                }
                else if (ret == POSICAO_INVALIDA)
                {
                    printf("Posição inválida \n");
                    break;
                }
            }

            //case 8: 
            // int qtd, count = 1;
            //     for (int i = 1; i <= TAM; i++)
            //     {
            //        qtd = getQuantidadeElementosEstruturaAuxiliar(i); 

            //        if(qtd == SUCESSO){
            //         count += qtd;
            //        }
            //     }

            //     int * vetorAux = malloc(count * sizeof(int));

            //     if(vetorAux == NULL){
            //         printf("Não tem espaço na memória para criar o vetorAux");
            //         break;
            //     }


            // break;
                
        case 10:
            int novoTamanho;

            printf("Posição e novo Tamanho: \n");
            scanf("%d %d", &posicao, &novoTamanho);

            ret = modificarTamanhoEstruturaAuxiliar(posicao, novoTamanho);

            if(ret == SUCESSO){
                printf("Sucesso \n");
                break;
            }else if(ret == SEM_ESTRUTURA_AUXILIAR){
                printf("Sem estrutura \n");
                break;
            }else if(ret == ESTRUTURA_AUXILIAR_VAZIA){
                printf("Estrutura vazia \n");
                break;
            }else if(ret == POSICAO_INVALIDA){
                printf("Posição inválida \n");
                break;
            }else if(ret == NOVO_TAMANHO_INVALIDO){
                printf("O novo tamanho é inválido");
                break;
            }

        default:
        {
            printf("opcao inválida\n");
        }
        }
    }

    return 0;
}
/*
    if(ret == SUCESSO){
                printf("Sucesso \n");
            }else if(ret == SEM_ESTRUTURA_AUXILIAR){
                printf("Sem estrutura \n");
            }else if(ret == ESTRUTURA_AUXILIAR_VAZIA){
                printf("Estrutura vazia \n");
            }else if(ret == POSICAO_INVALIDA){
                printf("Posição inválida \n");
            }
*/
