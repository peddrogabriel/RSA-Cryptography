#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

long long int eh_primo(long long int n)
{

    if(n <= 1){

        return 0;
    }

    if(n == 2){

        return 1;
    }

    else{

        if((n % 2) == 0){

            return 0;
        }
    }

    for(long long int i = 3; i <= n / i; i+=2){

        if(n % i == 0){
            
            return 0;
        }
    }

    return 1;
}

long long int mdc(long long int a, long long int b)
{
    long long int resto;

    if(b == 0)
    {
        return a;
    }

    while(a % b != 0)
    {
        resto = a % b;

        a = b;

        b = resto;
    }

    return b;
}

long long int coprimos(long long int a, long long int b)
{
    if(mdc(a,b) == 1){

        return 1;
    }

    else return 0;
}

long long int modular_otimizada(long long int a, long long int b, long long int modulo)
{
    long long int resultado = 0;

    while(b > 0)
    {
        if(b % 2 != 0){

            if(a >= modulo - resultado){

                resultado = a - (modulo - resultado);
            }

            else resultado = resultado + a;
    }

    if(a >= modulo - a){

        a = a - (modulo - a);
    }

    else a = a + a;

    b = b / 2;
    
    }

    return resultado;
}

long long int modular(long long int base, long long int expoente, long long int modulo)
{
    long long int resultado = 1;

    base = base % modulo;

    while(expoente > 0){

        if(expoente % 2 != 0){

            resultado = modular_otimizada(resultado, base, modulo);

        }

        base = modular_otimizada(base, base, modulo);

        expoente = expoente / 2;

    }
    
    return resultado;
}

long long int extensao(long long int a, long long int b)
{
    if(mdc(a,b) == 1){

    
        long long int x = 1;
        long long int x1 = 0;

        long long int y = 0;
        long long int y1 = 1;

        long long int resto, quociente;
        long long int modulo = b;

        while(b != 0){

            quociente = a / b;

            resto = a % b;

            a = b;

            b = resto;

            long long int aux_x = x;

            long long int aux_y = y;

            x = x1;

            x1 = aux_x - quociente * x1;

            y = y1;

            y1 = aux_y - quociente * y1;
        }

        x = (x % modulo + modulo) % modulo;

        return x;
    }

    else return -1;
}

long long int parametros(long long int p, long long int q, long long int *n, long long int *phi_euler)
{   
    if(p <= (LLONG_MAX / q) && p - 1 <= (LLONG_MAX / (q - 1))){

        *n = p * q;

        *phi_euler = (p-1) * (q-1); 

        return 1;
    }

    else return 0;
}
    
long long int expoente_publico(long long int phi_euler)
{
    long long int e;

    int apoio, ver;

    do
    {
        printf("Digite o valor de e:");

        apoio = scanf("%lld", &e);

        if(apoio == EOF)
        {
            return -1;
        }

        if(apoio == 0)
        {
            printf("Erro! Digite um numero: ");

            while((ver = getchar()) != '\n' && ver != EOF);

            if(ver == EOF)
            {
                return -1;
            }

            continue;
        }

        while((ver = getchar()) != '\n' && ver != EOF);

        if(e <= 1 || e >= phi_euler || coprimos(e, phi_euler) != 1)
        {
            printf("Numero invalido! Tente novamente.\n");
        }

    } while(e <= 1 || e >= phi_euler || coprimos(e, phi_euler) != 1);  
    
    return e;
} 

long long int expoente_privado(long long int e, long long int phi_euler)
{
    return extensao(e, phi_euler);  
}

typedef struct ChavesRSA{

    long long int e, d, n, phi_euler;

} ChavesRSA;

long long int chaves(long long int p, long long int q, ChavesRSA *chaves)
{
    long long int ver1 = eh_primo(p);

    long long int ver2 = eh_primo(q);

    if(ver1 == 1 && ver2 == 1 && p != q){

        long long int ver3 = parametros(p, q, &chaves -> n, &chaves -> phi_euler);

        if(ver3 == 1){

            if(chaves -> n > 28){

                chaves -> e = expoente_publico(chaves -> phi_euler);

                if(chaves -> e == -1){

                    return 0;
                }

                chaves -> d = expoente_privado(chaves -> e, chaves -> phi_euler);

                return 1;
        
            }

            else return 0;
        }

        else return 0;
    }

    else return 0;
}

long long int conversao(char frase[], long long int convertida[])
{
    size_t tamanho = strlen(frase);

    for(long long int tam = 0; tam < tamanho; tam++)
    {
        if((frase[tam] < 65 || frase[tam] > 90) && frase[tam] != 32)
        {
            printf("Mensagem Invalida! Digite apenas letras maiusculas, sem pontuacao.");

            return 0;
        }

        if(frase[tam] == ' '){

            convertida[tam] = 28;
        }

        else{

            convertida[tam] = frase[tam] - 63;

        }
    }

    return 1; 
}

void criptografar(long long int mensagem_convertida[], long long int criptografados[], long long int caracteres, ChavesRSA *chaves)
{
    for(long long int i = 0; i < caracteres; i++){

        criptografados[i]= modular(mensagem_convertida[i],chaves -> e, chaves -> n);
    }
}

long long int salvar_criptografado(long long int criptografados[], long long int quantidade, char nome_arquivo[])
{
    FILE *arquivo;

    arquivo = fopen(nome_arquivo, "w");

    if(arquivo == NULL){

        return 0;
    }

    int sucesso = 1;

    for(long long int i = 0; i < quantidade; i++){

        if(fprintf(arquivo, "%lld ", criptografados[i]) < 0){

            sucesso = 0;

            break;
        }
    }

    if(fclose(arquivo) == EOF){

        sucesso = 0;
    }

    return sucesso;
}

long long int *ler_criptografado(char nome_arquivo[], long long int *quantidade)
{
    FILE *arquivo;

    *quantidade = 0;

    long long int numero;

    arquivo = fopen(nome_arquivo, "r");

    if(arquivo != NULL){

       int leitura;

        while((leitura = fscanf(arquivo, "%lld", &numero)) == 1){

            (*quantidade)++;
        }

        if(leitura == 0){

            printf("Erro! O arquivo contem dados invalidos.\n");

            fclose(arquivo);

            return NULL;
        }

        if(*quantidade == 0)
        {
            printf("Erro! Nao existem numeros para serem lidos");

            fclose(arquivo);

            return NULL;     
        }

        long long int *armazenar = malloc((*quantidade) * sizeof(long long int));

        if(armazenar == NULL)
        {
            printf("Erro ao alocar memoria\n");

            fclose(arquivo);

            return NULL;
        }

        rewind(arquivo);

        for(long long int i = 0; i < *quantidade; i++)
        {
            if(fscanf(arquivo, "%lld", &armazenar[i]) != 1)
            {
                printf("Erro! Falha ao ler os numeros do arquivo.\n");

                free(armazenar);

                fclose(arquivo);

                return NULL;
            }
        }

        fclose(arquivo);

        return armazenar;
    }
    
    else return NULL;
}

void descriptografar(long long int criptografados[], long long int mensagem[], long long int quantidade, ChavesRSA *chaves)
{
    for(long long int i = 0; i < quantidade; i++){

        mensagem[i] = modular(criptografados[i], chaves->d, chaves->n);
    }
}

void desconversao(long long int mensagem[], char frase[], long long int quantidade)
{
    for(long long int i = 0; i < quantidade; i++){

        if(mensagem[i] == 28)
        {
            frase[i] = ' ';
        }

        else{
            
            frase[i] = mensagem[i] + 63;
        }
    }

    frase[quantidade] = '\0';
}

long long int salvar_descriptografado(char frase[], char nome_arquivo[])
{
    FILE *novo_arquivo;

    novo_arquivo = fopen(nome_arquivo, "w");

    if(novo_arquivo == NULL){

        return 0;
    }

    int sucesso = 1;

    if(fprintf(novo_arquivo, "%s", frase) < 0){

        sucesso = 0;
    }
    
    if(fclose(novo_arquivo) == EOF){

        sucesso = 0;
    }

    return sucesso;
}

long long int chave_publica(ChavesRSA *chaves, char nome_arquivo[])
{
    FILE *arquivo_publico;

    arquivo_publico = fopen(nome_arquivo,"w");

    if(arquivo_publico == NULL){

        return 0;
    }

    int sucesso = 1;
    
    if(fprintf(arquivo_publico, "%lld\n%lld", chaves->n, chaves->e) < 0){

        sucesso = 0;
    }

    if(fclose(arquivo_publico) == EOF){
        
        sucesso = 0;
    }

    return sucesso;   
}

int ler_chave_publica(char nome_arquivo[], ChavesRSA *chaves)
{
    FILE *arquivo_chave_publica;

    arquivo_chave_publica = fopen(nome_arquivo, "r");

    if(arquivo_chave_publica != NULL)
    {
        if(fscanf(arquivo_chave_publica, "%lld%lld", &chaves -> n, &chaves -> e) == 2){

            fclose(arquivo_chave_publica);

            return 1;
        }

        else{

            fclose(arquivo_chave_publica);

            return 0;
        } 
    }

    else return 0;
}

int main()
{
    long long int opcao;

    do {
        
        printf("\n\nBem vindo ao PROJETO_RSA - CRIPTOGRAFIA!\n\nEscolha uma das opcoes e digite o numero correspondente:\n\n(1)- Gerar chave publica\n\n(2)- Criptografar mensagem\n\n(3)- Descriptografar mensagem\n\n(0)- Sair do programa\n\n");

        int apoio = scanf("%lld", &opcao);

        if(apoio == 0){

            int ver = getchar();

            printf("Erro! Digite um numero");

            while(ver != '\n' && ver != EOF)
            {
                ver =  getchar();
            }

            continue;
        }

        if(apoio == EOF){

            break;
        }

        int suporte = getchar();

        while(suporte != '\n' && suporte != EOF)
        {
            suporte =  getchar();
        }

        switch(opcao)
        {
            case 1: {

                printf("Gerando chave publica.....\n\n");

                ChavesRSA minha_chave;
            
                long long int p, q;

                printf("Digite o valor de p:");

                int apoio = scanf("%lld", &p);

                if(apoio == 0){

                    int ver = getchar();

                    printf("Erro! Digite um numero");

                    while(ver != '\n' && ver != EOF)
                    {
                        ver =  getchar();
                    }

                    continue;
                }

                if(apoio == EOF){

                    break;
                }

                int olhar = getchar();

                while(olhar != '\n' && olhar != EOF)
                {
                    olhar =  getchar();
                }

                printf("Digite o valor de q:");

                apoio = scanf("%lld", &q);

                if(apoio == 0){

                    int ver = getchar();

                    printf("Erro! Digite um numero");

                    while(ver != '\n' && ver != EOF)
                    {
                        ver =  getchar();
                    }

                    continue;
                }

                if(apoio == EOF){

                    break;
                }

                long long int armazenar = chaves(p, q, &minha_chave);

                if(armazenar == 1){

                    if(chave_publica(&minha_chave, "chave_publica.txt") == 1){

                        printf("Chave publica salva com sucesso!\n");
                    }

                    else{

                        printf("Erro ao salvar a chave publica!\n");
                    }
                }

                else printf("Erro na geracao da chave publica!\n");

                break;
            }

            case 2: {

                int armazena_mensagem;

                int erro = 0;

                ChavesRSA minha_chave;

                long long int capacidade = 20;

                long long int tamanho = 0;

                int verificacao = ler_chave_publica("chave_publica.txt", &minha_chave);

                if(verificacao == 0){

                    printf("Nao foi possivel carregar a chave publica\n");
                    
                    break;
                }

                else{

                    printf("Digite a frase que vai ser criptografada:");

                    armazena_mensagem = getchar();

                    char *frase = malloc((capacidade) * sizeof(char));

                    if(frase == NULL){

                        printf("Erro ao alocar memoria!\n");

                        break;
                    }

                    else{

                        while(armazena_mensagem != '\n' && armazena_mensagem != EOF){

                            frase[tamanho] = armazena_mensagem;

                            tamanho ++;

                            if(tamanho == capacidade - 1){

                                char *temporario;

                                capacidade = capacidade * 2;

                                temporario = realloc(frase, (capacidade) * sizeof(char));

                                if(temporario != NULL){

                                 frase = temporario;
                                }

                                else {
                            
                                    free(frase);

                                    erro ++;

                                    break;
                                }

                            }

                            armazena_mensagem = getchar();
 
                        }

                        if(erro == 1){

                            printf("Erro ao expandir a memoria da mensagem!\n");

                            break;
                        }

                        if(tamanho == 0)
                        {
                            printf("Erro! Mensagem vazia!");

                            free(frase);

                            break;
                        }
            
                        frase[tamanho] = '\0';

                        long long int *convertida;

                        convertida = malloc((tamanho) * sizeof(long long int));

                        if(convertida == NULL){

                            printf("Erro ao alocar memoria!\n");

                            free(frase);

                            break;
                        }

                        else{

                            int verificando = conversao(frase, convertida);

                            if(verificando == 0)
                            {
        
                                free(frase);
                                free(convertida);

                                break;
                            }

                            else{printf("Conversao concluida com sucesso!\n");}           
                        }

                        long long int *criptografados;

                        criptografados = malloc((tamanho) * sizeof(long long int));

                        if(criptografados == NULL){

                            printf("Erro ao alocar memoria!\n");

                            free(frase);
                            free(convertida);

                            break;
                        }

                        else{

                            criptografar(convertida, criptografados, tamanho, &minha_chave);
                        }

                        if(salvar_criptografado(criptografados, tamanho, "mensagem_criptografada.txt") == 1){

                            printf("Mensagem criptografada e salva com sucesso!\n");
                        }

                        else{

                            printf("Erro ao salvar a mensagem criptografada!\n");
                        }

                        free(frase);
                        free(convertida);
                        free(criptografados);

                    }
                }

                break;
            }

            case 3: {

                long long int p, q;

                long long int quantidade;

                ChavesRSA minha_chave;

                printf("Digite o valor de p:");

                int apoio = scanf("%lld", &p);

                if(apoio == 0){

                    int ver = getchar();

                    printf("Erro! Digite um numero");

                    while(ver != '\n' && ver != EOF)
                    {
                        ver =  getchar();
                    }

                    continue;
                }

                if(apoio == EOF){

                    break;
                }

                int olhar = getchar();

                while(olhar != '\n' && olhar != EOF)
                {
                    olhar =  getchar();
                }

                printf("Digite o valor de q:");

                apoio = scanf("%lld", &q);

                if(apoio == 0){

                    int ver = getchar();

                    printf("Erro! Digite um numero");

                    while(ver != '\n' && ver != EOF)
                    {
                        ver =  getchar();
                    }

                    continue;
                }

                if(apoio == EOF){

                    break;
                }

                int verificacao = chaves(p, q, &minha_chave);

                if(verificacao == 1){

                    long long int *criptografados;

                    criptografados = ler_criptografado("mensagem_criptografada.txt", &quantidade);

                    if(criptografados ==  NULL){

                        printf("Erro ao ler dados criptografados!\n");

                        break;
                    }

                    else{

                        long long int *mensagem;

                        mensagem = malloc((quantidade) * sizeof(long long int));

                        if(mensagem == NULL)
                        {
                            printf("Erro ao alocar memoria!\n");

                            free(criptografados);

                            break;
                        }

                        else{

                            descriptografar(criptografados, mensagem, quantidade, &minha_chave);

                            char *frase;

                            frase = malloc((quantidade + 1) *sizeof(char));

                            if(frase == NULL)
                            {
                                printf("Erro ao alocar memoria!\n");

                                free(criptografados);
                                free(mensagem);

                                break;
                            }

                            else{

                                desconversao(mensagem, frase, quantidade);

                                if(salvar_descriptografado(frase, "mensagem_descriptografada.txt") == 1){

                                    printf("Mensagem descriptografada e salva com sucesso!\n");
                                }
                                
                                else{

                                    printf("Erro ao salvar a mensagem descriptografada!\n");
                                }

                                free(mensagem);
                                free(frase);
                                free(criptografados);

                                break;
                            }
                        }
                    }  
                }

                else {

                    printf("Falha ao gerar chaves RSA!\n");

                    break;
                }
            }

            case 0: {

                printf("Programa encerrado!\n");

                break;
            }

            default: {

                printf("Opcao invalida! Tente novamente.\n");

                break;
            }
        } 

    } while(opcao != 0);


    return 0;
}