#include <stdio.h>
#include <locale.h>
#include <string.h> // biblioteca da funcao strlen (captura o tamanho da palavra dentro de um array de chars)
#include "forca.h" // header file
#include <stdlib.h>
#include <time.h>

// variaveis globais: 

char palavraSecreta [20]; //importante lembrar que vetores em C, sempre se inicializa na posicao 0
char chutes[26];
int chutesDados = 0;

// funcao responsavel por imprimir o cabecalho:

void abertura (){
    printf(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
    printf("\n                Bem vindo ao                                                                 \n");
    printf("                               J o g o                                                       \n");
    printf("                                       d a                                                   \n");
    printf("                                            f o r c a                                        \n");
    printf("                                             /|/                                             \n");
    printf("                                            #####                                            \n");
    printf("                                             / /                                             \n");
    printf("\n>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>\n");
}

// funcao que permite o usuario chutar uma letra:
void chuta (){  
    char chute;
    printf("Desafie-se chutando a letra: \n");
    scanf(" %c",&chute);

    chutes[chutesDados] = chute; 
    chutesDados++;
}

// funcao responsavel por informar se o usuario ja chutou determinada letra:

int jaChutou (char letra) {
    int achou = 0;

        for (int j = 0; j < chutesDados; j++){
                if(chutes[j] == letra){
                    achou = 1;
                    break;
                }
        }
    
    return achou;
}

// funcao responsavel por imprimir as letras e o traco da forca:

void desenhaForca() {

    int erros = chutesErrados ();

    // utilizamos o operador ternário para desenhar o boneco da forca, ou seja:
    // condição ? valor se for verdadeiro : valor se for falso

    printf("  _______       \n");
	printf(" |/      |      \n");
	printf(" |      %c%c%c  \n", (erros>=1?'(':' '), (erros>=1?'_':' '), (erros>=1?')':' '));
	printf(" |      %c%c%c  \n", (erros>=3?'\\':' '), (erros>=2?'|':' '), (erros>=3?'/': ' '));
	printf(" |       %c     \n", (erros>=2?'|':' '));
	printf(" |      %c %c   \n", (erros>=4?'/':' '), (erros>=4?'\\':' '));
	printf(" |              \n");
	printf("_|___           \n");
	printf("\n\n");

    //imprime a palavra secreta
        for(unsigned long i = 0; i < strlen(palavraSecreta); i++) {
            
            // condicional que decide mostrar ou nao a letra
            if(jaChutou(palavraSecreta[i])){  //chama a funcao jaChutou
                printf("%c ", palavraSecreta[i]);
            } else {
                printf("_ ");
            }
        }
    printf("\n");
}

// funcao que permite selecionar a palavra secreta
void escolhePalavra (){
    
    FILE*f;

    f = fopen("palavras.txt", "r");

        if (f == 0){
            printf("Banco de dados de palavras não disponível no momento\n");
            exit(1);
        }
    int qtdPalavras;
    fscanf(f,"%d", &qtdPalavras); 

    srand(time(0));
    int randomico = rand () %qtdPalavras;

    for (int i = 0; i <= randomico; i++){
        fscanf(f,"%s",palavraSecreta);
    }

    fclose(f);
}

// funcao responsavel pela a logica que informa se o usuario ganhou o jogo
int ganhou () {

    for(unsigned long i = 0; i <strlen(palavraSecreta); i++){
        
        if(!jaChutou(palavraSecreta[i])){ // se a palavra secreta nao foi chutada
            return 0;
        }
    }

    return 1;
}

int chutesErrados() {

    int erros = 0; // variável que contará o número de letras que o usuário chutou de maneira incorreta

        // loop em todos os chutes dados:
        for(int i = 0; i < chutesDados; i++){
            int existe = 0;
        
            // olha a letra da palavra secreta e ver se encontra o chute aqui
            for(unsigned long j = 0; j < strlen(palavraSecreta); j++){
                if (chutes[i] == palavraSecreta[j]){
                    existe = 1;
                    break;
                }
            }
            if (!existe) {
                erros++;
             }
    }

    return erros;
}

// funcao responsavel pela a logica que informa se o usuário perdeu o jogo, ou seja, esgotou suas tentativas
int enforcou (){

    return chutesErrados() >= 5;
}

// função para adicionar novas palavras no final da partida

void adicionaPalavra (){
    char quer;

    printf("Você deseja adicionar uma nova palavra no JOGO (S/N)?");
    scanf(" %c", &quer);

    if (quer == 'S'){
         char novaPalavra[20];

        printf("Digite a nova palavra, em letras maiúsculas: ");
        scanf("%s", novaPalavra);

        FILE*f;

        f = fopen ("palavras.txt", "r+");
        
        if (f == 0){
            printf("Banco de dados de palavras não disponível no momento\n");
            exit(1);
        }

    int qtd;
    fscanf(f,"%d", &qtd);
    qtd++;
    fseek(f, 0,SEEK_SET);
    fprintf(f,"%d", qtd);

    fseek(f, 0 , SEEK_END);
    fprintf(f,"\n%s", novaPalavra);
    
    fclose(f);

    }
}

int main () {

    setlocale(LC_ALL, "Portuguese");

    escolhePalavra();
    abertura ();

    do {

        desenhaForca();
        chuta (); //& = p/passar o endereço de memória da variável tentativas p/ a função chuta
        
    } while (!ganhou() && !enforcou());
    

    if(ganhou()){
        
        printf("\nParabéns, você ganhou!\n\n");

		printf("       ___________      \n");
		printf("      '._==_==_=_.'     \n");
		printf("      .-\\:      /-.    \n");
		printf("     | (|:.     |) |    \n");
		printf("      '-|:.     |-'     \n");
		printf("        \\::.    /      \n");
		printf("         '::. .'        \n");
		printf("           ) (          \n");
		printf("         _.' '._        \n");
		printf("        '-------'       \n\n");

    } else {
        printf("\nQue pena, você perdeu\n\n");
        printf("\nA palavra era %s\n\n", palavraSecreta);

        printf("    _______________         \n");
		printf("   /               \\       \n"); 
		printf("  /                 \\      \n");
		printf("//                   \\/\\  \n");
		printf("\\|   XXXX     XXXX   | /   \n");
		printf(" |   XXXX     XXXX   |/     \n");
		printf(" |   XXX       XXX   |      \n");
		printf(" |                   |      \n");
		printf(" \\__      XXX      __/     \n");
		printf("   |\\     XXX     /|       \n");
		printf("   | |           | |        \n");
		printf("   | I I I I I I I |        \n");
		printf("   |  I I I I I I  |        \n");
		printf("   \\_             _/       \n");
		printf("     \\_         _/         \n");
		printf("       \\_______/           \n");

    }

    adicionaPalavra();
    return 0;
}


    