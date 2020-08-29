#include <stdio.h>
#include <stdlib.h>

#ifdef __unix__
  #define cls_ system("clear")
  #include <termios.h>
  #include <unistd.h>
  #define scnf pos=getx()-48
  #define jdnv jogarNovamente=getx()-48

  int getx(void){
    struct termios f1;
      int dgt;
        tcgetattr( STDIN_FILENO, &f1 );
        f1.c_lflag &= ~( ICANON | ECHO );
        tcsetattr( STDIN_FILENO, TCSANOW, &f1 );
        dgt = getchar();
        return dgt;
  }
#endif

#if defined WIN32 || defined _WIN32
  #define cls_ system("cls")
  #include <conio.h>
  #define scnf pos=getch()-48
  #define jdnv jogarNovamente=getch()-48
#endif

////////////////////////////////////////////////////////////////////////////////////////////////////////////

void mapa(char velh[3][3]){
  printf("\n\n\n\n\n==================== JOGO DA VELHA ====================\n\n\n");
  printf("\t               %c | %c | %c  \n", velh[0][0], velh[0][1], velh[0][2]);
  printf("\t              ——— ——— ———    \n");
  printf("\t               %c | %c | %c  \n", velh[1][0], velh[1][1], velh[1][2]);
  printf("\t              ——— ——— ———    \n");
  printf("\t               %c | %c | %c  \n" , velh[2][0], velh[2][1], velh[2][2]);
}

void jogardnv(){
  printf("\n\n---------------------------------------------");
  printf("\nPRESSIONE QUALQUER TECLA PARA JOGAR NOVAMENTE"),
  printf("\nPRESSIONE 0 PARA SAIR");
  printf("\n---------------------------------------------\n");
}

int main() {
  int jogarNovamente=2; char OX=' ', pos;

  printf("\nBEM VINDO(A) AO JOGO DA VELHA\n\nESSES SÃO OS COMANDOS DAS CASAS:");
  printf("\n\n==================== JOGO DA VELHA ====================\n\n\n");
  printf("\t               1 | 2 | 3     \n");
  printf("\t              ——— ——— ———    \n");
  printf("\t               4 | 5 | 6     \n");
  printf("\t              ——— ——— ———    \n");
  printf("\t               7 | 8 | 9     \n");
  printf("\nJOGADOR 1: 'X'\nJOGADOR 2: 'O'\n\n\t|PRESSIONE QUALQUER TECLA PARA CONTINUAR|\n");
  scnf;

  while(jogarNovamente != 0){

    char velha[3][3];
    int pos, jogar = 0, player = 1, vitoria=0, acerto=0, vez=0;

    cls_; jogar=1;

    for(int c = 0; c<3; c++){
      for(int x = 0; x<3; x++){
        velha[c][x]=' ';
      }
    }

    while(jogar == 1){ /*conf;*/ cls_; mapa(velha);

      (vez>0) ? printf("\nA POSIÇÃO [%d] NÃO PODE SER USADA", pos) : ' ';

      if(player==1) OX='X'; else OX='O';
      printf("\n\nVEZ DO JOGADOR %d\nDigite sua jogada: ", player);
      scnf;

      (pos == 1 && (velha[0][0]==' ') ) ? velha[0][0] = OX, acerto++ :
      (pos == 2 && (velha[0][1]==' ') ) ? velha[0][1] = OX, acerto++ :
      (pos == 3 && (velha[0][2]==' ') ) ? velha[0][2] = OX, acerto++ :
      (pos == 4 && (velha[1][0]==' ') ) ? velha[1][0] = OX, acerto++ :
      (pos == 5 && (velha[1][1]==' ') ) ? velha[1][1] = OX, acerto++ :
      (pos == 6 && (velha[1][2]==' ') ) ? velha[1][2] = OX, acerto++ :
      (pos == 7 && (velha[2][0]==' ') ) ? velha[2][0] = OX, acerto++ :
      (pos == 8 && (velha[2][1]==' ') ) ? velha[2][1] = OX, acerto++ :
      (pos == 9 && (velha[2][2]==' ') ) ? velha[2][2] = OX, acerto++ : vez++;

    //VERIFICAÇÃO DO VENCEDOR
      (  (velha[0][0]==OX && velha[0][1]==OX && velha[0][2]==OX) ||
         (velha[1][0]==OX && velha[1][1]==OX && velha[1][2]==OX) ||
         (velha[2][0]==OX && velha[2][1]==OX && velha[2][2]==OX) ||

         (velha[0][0]==OX && velha[1][0]==OX && velha[2][0]==OX) ||
         (velha[0][1]==OX && velha[1][1]==OX && velha[2][1]==OX))||
         (velha[0][2]==OX && velha[1][2]==OX && velha[2][2]==OX) ||

         (velha[0][0]==OX && velha[1][1]==OX && velha[2][2]==OX) ||
         (velha[0][2]==OX && velha[1][1]==OX && velha[2][0]==OX) ?
         cls_, mapa(velha), printf("\n\nPARABÉNS!!! JOGADOR %d É O VENCEDOR!", player), vitoria=1, jogar=0,

         jogardnv(),
         jdnv : //

    //VERIFICAÇÃO DE EMPATE
      (  (velha[0][0]!=' ' && velha[0][1]!=' ' && velha[0][2]!=' ' &&
          velha[1][0]!=' ' && velha[1][1]!=' ' && velha[1][2]!=' ' &&
          velha[2][0]!=' ' && velha[2][1]!=' ' && velha[2][2]!=' ')  &&
         (jogar==1 || jogar==0) && vitoria!=1 ) ? jogar=0, cls_, mapa(velha), printf("\n\nDEU VELHA!!"),

         jogardnv(),
         jdnv : ' '; //

      if(jogarNovamente==0){ cls_, printf("\nOBRIGADO POR JOGAR!!!"); }

     (acerto>0) ? ( (player==1) ? player++ : player-- ), vez=0, acerto=0 : acerto==0;

    }
  }

 return 0;
}