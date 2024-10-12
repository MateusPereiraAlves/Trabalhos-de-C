#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

//----------------------ESTRUTURAS----------------------//

//Estrutura livros disponiveis
typedef struct LivroDisp
{
    int cod;
    char titulo[50];
    char assunto[100];
    char autor[50];
} livroDisp;

//Estrutura livros emprestados
typedef struct LivrosEmp
{
    int cod_cliente;
    livroDisp livro;
} livroEmp;

//Lista livros disponiveis
struct noLivrosDisp
{
    livroDisp info_livros_disp;
    struct noLivrosDisp *prox;
};

typedef struct noLivrosDisp NoLivrosDisp;
typedef struct noLivrosDisp ListaLivrosDisp;

//Lista livros emprestados
struct noLivrosEmp
{
    livroEmp info_livros_emp;
    struct noLivrosEmp *prox;
};

typedef struct noLivrosEmp NoLivrosEmp;
typedef struct noLivrosEmp ListaLivrosEmp;

//Estrutura clientes;
typedef struct Cliente
{
    int cod;
    char nome[50];
    ListaLivrosDisp *livros;
} cliente;

//Lista clientes
struct noCliente
{
    cliente info_cliente;
    struct noCliente *prox;
};

typedef struct noCliente NoCliente;
typedef struct noCliente ListaCliente;

//----------------------CABECALHO DAS FUNCOES----------------------//

//CLIENTE:
ListaCliente* insereCliente(ListaCliente *Lista, cliente Cliente);

cliente lerCliente();

void imprimeListaCliente(ListaCliente *Lista);

void imprimirLivrosCliente(ListaCliente *Lista, int codCliente);


//LIVROS DISPONIVEIS:
void insereLivroDisp(ListaLivrosDisp **Lista, livroDisp Livro);

void removeLivroDisp(ListaLivrosDisp **Lista, int codLivro);

livroDisp lerLivroDisp();

void imprimeListaLivrosDisp(ListaLivrosDisp *Lista);

void imprimeLivroDisp(livroDisp Livro);


//LIVROS EMPRESTADOS:
ListaLivrosEmp* insereLivroEmp(ListaLivrosEmp *listaLivrosEmp, ListaLivrosDisp **listaLivrosDisp, ListaCliente **listaClientes, livroEmp Livro, int codCliente);

ListaLivrosEmp* removeLivroEmp(ListaLivrosEmp *listaLivrosEmp, ListaLivrosDisp **listaLivrosDisp, ListaCliente **listaClientes, int codLivro, int codCliente);

livroEmp lerLivroEmp(ListaLivrosDisp *listaLivrosDisp);

void imprimeListaLivrosEmp(ListaLivrosEmp *Lista);


//----------------------MAIN----------------------//

int main()
{
    setlocale(LC_ALL, "portuguese");

    ListaCliente *listaCliente = NULL;
    ListaLivrosDisp *listaLivrosDisp = NULL;
    ListaLivrosEmp *listaLivrosEmp = NULL;

    int ClienteEscolhido;
    int LivroEscolhido;
    
    int escolha = 0;
    do
    {
        printf("\n\nDigite a opção desejada:");
        printf("\n1)Inserir um livro novo na biblioteca");
        printf("\n2)Inserir um novo cliente");
        printf("\n3)Emprestar um livro para um cliente");
        printf("\n4)Devolver um livro de um determinado cliente");
        printf("\n5)Imprimir os livros que estão emprestados por um dado cliente");
        printf("\n6)Imprimir a Lista de todos os clientes com os respectivos livros emprestados");
        printf("\n7)Imprimir a Lista de Todos os Livros Emprestado");
        printf("\n8)Imprimir a lista de Livros Disponíveis da Biblioteca");
        printf("\n9)Sair do Sistema\n");

        if (scanf("\n%d", &escolha) != 1)
        {
            printf("Entrada inválida. Por favor, insira um número.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (escolha)
        {
            case 1:
            printf("\nInserindo livro:\n");
            livroDisp novoLivroDisp1 = lerLivroDisp();
            insereLivroDisp(&listaLivrosDisp, novoLivroDisp1);
            break;

            case 2:
            printf("Inserindo cliente:\n");
            cliente novoCliente1 = lerCliente();
            listaCliente = insereCliente(listaCliente, novoCliente1);
            break;

            case 3:
            printf("\nEmprestando livro:\n");
            livroEmp livroEmp1 = lerLivroEmp(listaLivrosDisp);
            listaLivrosEmp = insereLivroEmp(listaLivrosEmp, &listaLivrosDisp, &listaCliente, livroEmp1, livroEmp1.cod_cliente);
            break;

            case 4:
            printf("\nCódigo do cliente desejado: \n");
            scanf("%d",&ClienteEscolhido);
            printf("\nImprimindo livros do cliente %d:\n", ClienteEscolhido);
            imprimirLivrosCliente(listaCliente, ClienteEscolhido);
            printf("\nCódigo do livro a ser devolvido: \n");
            scanf("%d",&LivroEscolhido);
            printf("\nDevolvendo livro...\n");
            listaLivrosEmp = removeLivroEmp(listaLivrosEmp, &listaLivrosDisp, &listaCliente, LivroEscolhido, ClienteEscolhido);
            break;

            case 5:
            printf("\nCódigo do cliente desejado: \n");
            scanf("%d",&ClienteEscolhido);
            printf("\nImprimindo livros do cliente %d:\n", ClienteEscolhido);
            imprimirLivrosCliente(listaCliente, ClienteEscolhido);
            break;

            case 6:
            printf("\nImprimindo lista de clientes:\n");
            imprimeListaCliente(listaCliente);
            break;

            case 7:
            printf("\nImprimindo livros emprestados:\n");
            imprimeListaLivrosEmp(listaLivrosEmp);
            break;

            case 8:
            printf("\nImprimindo livros disponiveis:\n");
            imprimeListaLivrosDisp(listaLivrosDisp);
            break;

            case 9:
            printf ("Fim do programa!");
            break;

            default :
            printf ("Valor invalido!\n");
        } 
    }while(escolha!=9); 

    return 0;
}




//----------------------CORPO DAS FUNCOES----------------------//

//CLIENTE:

//Insere um novo cliente na lista
ListaCliente* insereCliente(ListaCliente *Lista, cliente Cliente)
{
    NoCliente *novoNo = (NoCliente*)malloc(sizeof(NoCliente));
    novoNo->info_cliente = Cliente;
    novoNo->prox = NULL;

    if (Lista == NULL)
    {
        Lista = novoNo;
    }
    else
    {
        NoCliente *aux = Lista;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
    return Lista;
}

//Imprime a lista de clientes
void imprimeListaCliente(ListaCliente *Lista)
{
    if (Lista == NULL)
    {
        printf("A lista de clientes esta vazia\n");
    }
    else
    {
        ListaCliente *aux = Lista;
        while(aux != NULL)
        {
            printf("  Codigo: %d\n", aux->info_cliente.cod);
            printf("  Nome: %s\n", aux->info_cliente.nome);
            NoLivrosDisp *aux2 = aux->info_cliente.livros;
            if (aux2 == NULL)
            {
                printf("  O cliente nao tem livros.\n");
            }
            else
            {
                printf("  LIRVOS: \n");
                while (aux2 != NULL)
                {
                    imprimeLivroDisp(aux2->info_livros_disp);
                    aux2 = aux2->prox;
                }
            }
            aux = aux->prox;
        }
    }
}

//Le um novo cliente
cliente lerCliente()
{
    cliente novoCliente;

    do
    {
        printf("Digite o codigo de identificacao do cliente: ");

        if (scanf("%d", &novoCliente.cod) != 1 || novoCliente.cod < 0)
        {
            printf("Entrada inválida. Por favor, insira um número positivo.\n");
            while (getchar() != '\n');
            continue;
        }
    } while (novoCliente.cod < 0);
    
    printf("Digite o nome do cliente: ");
    scanf(" %s", &novoCliente.nome);

    novoCliente.livros = NULL;
    return novoCliente;
}

void imprimirLivrosCliente(ListaCliente *Lista, int codCliente)
{
    ListaCliente *aux = Lista;
    while(aux != NULL)
    {
        if (aux->info_cliente.cod == codCliente)
        {
            ListaLivrosDisp *aux2 = aux->info_cliente.livros;

            if (aux2 == NULL)
            {
                printf("O cliente nao tem livros.\n");
                break;
            }
            else
            {
                while (aux2 != NULL)
                {
                    imprimeLivroDisp(aux2->info_livros_disp);
                    aux2 = aux2->prox;
                }
                return;
            }
        }
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        printf("Cliente nao encontrado\n");
    }
}


//LIVROS DISPONIVEIS:

//Insere um novo livro na lista de livros disponiveis
void insereLivroDisp(ListaLivrosDisp **Lista, livroDisp Livro)
{
    NoLivrosDisp *novoNo = (NoLivrosDisp*)malloc(sizeof(NoLivrosDisp));
    novoNo->info_livros_disp = Livro;
    novoNo->prox = NULL;

    if (*Lista == NULL)
    {
        *Lista = novoNo;
    }
    else
    {
        NoLivrosDisp *aux = *Lista;
        while (aux->prox != NULL)
        {
            aux = aux->prox;
        }
        aux->prox = novoNo;
    }
}


//Remove um livro da lista de livros disponíveis
void removeLivroDisp(ListaLivrosDisp **Lista, int codLivro)
{
    NoLivrosDisp *atual = *Lista;
    NoLivrosDisp *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->info_livros_disp.cod == codLivro)
        {
            //Se o livro tá no inicio da lista
            if (anterior == NULL)
            {
                *Lista = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
}


//Imprime a lista de livros disponiveis
void imprimeListaLivrosDisp(ListaLivrosDisp *Lista)
{
    if (Lista == NULL)
    {
        printf("A lista de livros disponiveis esta vazia\n");
    }
    else
    {
        ListaLivrosDisp *aux = Lista;
        while(aux != NULL)
        {
            imprimeLivroDisp(aux->info_livros_disp);
            aux = aux->prox;
        }
    }
}

//Le um novo livro disponivel
livroDisp lerLivroDisp()
{
    livroDisp novoLivro;

    do
    {
        printf("Codigo: ");
        if (scanf("%d", &novoLivro.cod) != 1 || novoLivro.cod < 0)
        {
            printf("Entrada inválida. Por favor, insira um número positivo.\n");
            while (getchar() != '\n');
            continue;
        }
    } while (novoLivro.cod < 0);

    printf("Titulo: ");
    scanf(" %s", &novoLivro.titulo);

    printf("Assunto: ");
    scanf(" %s", &novoLivro.assunto);

    printf("Autor: ");
    scanf(" %s", &novoLivro.autor);

    return novoLivro;
}

void imprimeLivroDisp(livroDisp Livro)
{
    printf("  Codigo: %d\n", Livro.cod);
    printf("  Titulo: %s\n", Livro.titulo);
    printf("  Assunto: %s\n", Livro.assunto);
    printf("  Autor: %s\n\n", Livro.autor);
}


//LIRVOS EMPRESTADOS:

//Insere um novo livro na lista de livros disponiveis
ListaLivrosEmp* insereLivroEmp(ListaLivrosEmp *listaLivrosEmp, ListaLivrosDisp **listaLivrosDisp, ListaCliente **listaClientes, livroEmp Livro, int codCliente)
{
    if (Livro.livro.cod == -1)
    {
        printf("Livro nao encontrado.\n");
        return listaLivrosEmp;
    }
    else
    {
        NoCliente *aux2 = *listaClientes;
        while (aux2 != NULL)
        {
            if (aux2->info_cliente.cod == codCliente)
            {
                insereLivroDisp(&(aux2->info_cliente.livros), Livro.livro);
                break;
            }
            aux2 = aux2->prox;
        }
        if (aux2 == NULL)
        {
            printf("Cliente nao encontrado\n");
            return listaLivrosEmp;
        }

        removeLivroDisp(listaLivrosDisp, Livro.livro.cod);
        NoLivrosEmp *novoNo = (NoLivrosEmp*)malloc(sizeof(NoLivrosEmp));
        novoNo->info_livros_emp = Livro;
        novoNo->prox = NULL;

        if (listaLivrosEmp == NULL)
        {
            listaLivrosEmp = novoNo;
        }
        else
        {
            NoLivrosEmp *aux = listaLivrosEmp;
            while (aux->prox != NULL)
            {
                aux = aux->prox;
            }
            aux->prox = novoNo;
        }
    }

    return listaLivrosEmp;
}


//Remove um livro da lista de livros disponíveis
ListaLivrosEmp* removeLivroEmp(ListaLivrosEmp *listaLivrosEmp, ListaLivrosDisp **listaLivrosDisp, ListaCliente **listaClientes, int codLivro, int codCliente)
{
    NoCliente *aux2 = *listaClientes;
    while (aux2 != NULL)
    {
        if (aux2->info_cliente.cod == codCliente)
        {
            removeLivroDisp(&(aux2->info_cliente.livros), codLivro);
            break;
        }
        aux2 = aux2->prox;
    }
    if (aux2 == NULL)
    {
        printf("Cliente nao encontrado\n");
        return listaLivrosEmp;
    }
    
    
    NoLivrosEmp *atual = listaLivrosEmp;
    NoLivrosEmp *anterior = NULL;

    while (atual != NULL)
    {
        if (atual->info_livros_emp.livro.cod == codLivro)
        {
            //Se o livro tá no inicio da lista
            if (anterior == NULL)
            {
                listaLivrosEmp = atual->prox;
            }
            else
            {
                anterior->prox = atual->prox;
            }
            insereLivroDisp(listaLivrosDisp, atual->info_livros_emp.livro);
            free(atual);
            break;
        }
        anterior = atual;
        atual = atual->prox;
    }
    if (atual == NULL)
    {
        printf("Livro nao encontrado\n");
        return listaLivrosEmp;
    }

    return listaLivrosEmp;
}



//Imprime a lista de livros disponiveis
void imprimeListaLivrosEmp(ListaLivrosEmp *Lista)
{
    if (Lista == NULL)
    {
        printf("A lista de livros emprestados esta vazia\n");
    }
    else
    {
        ListaLivrosEmp *aux = Lista;
        while(aux != NULL)
        {
            printf("  Cliente: %d\n", aux->info_livros_emp.cod_cliente);
            imprimeLivroDisp(aux->info_livros_emp.livro);
            aux = aux->prox;
        }
    }
}



//Le um novo livro disponivel
livroEmp lerLivroEmp(ListaLivrosDisp *Lista)
{
    livroEmp novoLivro;

    printf("Codigo do livro: ");
    scanf("%d", &novoLivro.livro.cod);

    printf("Codigo do cliente: ");
    scanf(" %d", &novoLivro.cod_cliente);

    NoLivrosDisp *aux = Lista;
    while (aux != NULL)
    {
        if (aux->info_livros_disp.cod == novoLivro.livro.cod)
        {
            novoLivro.livro = aux->info_livros_disp;
            break;
        }
        aux = aux->prox;
    }
    if (aux == NULL)
    {
        novoLivro.livro.cod = -1;
    }

    return novoLivro;
}


