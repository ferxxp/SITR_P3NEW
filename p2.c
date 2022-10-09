/* Creación de colas de mensajes, envío de datos */
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
/* Definición de la clave de la cola */
#define M_1 1
/* Prototipos */
int crearcola(int key);
/* Función principal */
int main(void)
{
  int a=1;
  char b='a';
  printf("%ld\n",sizeof(a) );
  printf("%ld\n",sizeof(b) );
int msg1, i;
/*struct msgbuf time_msg;
struct msgbuf presenta dos campos:
long mtype, permite definir al usuario una etiqueta asociada al mensaje.
char mtext[], texto del mensaje que se envía. */
struct msgbuf
{
long mtype;
char mtext[4];
} time_msg;
/* Llamada a la función de creación de colas */
msg1=crearcola(M_1);
/* Inicialización de los campos de la estructura */
do
{
  /* unsigned int sleep(unsigned int seconds): provoca una espera en segundos, en función del
  valor del parámetro */
  //sleep(1);
  printf("Introduce numero: ");
  fflush(stdin);
  char c_num[4];
  scanf("%s",c_num);
  strcpy(time_msg.mtext, c_num);
  time_msg.mtype = 1;
  //time_msg.mtext[0]++;
  /* int msgsnd(int msg, struct msgbuf * buf, int size, int flag): envía el mensaje almacenado en
  el segundo campo de buf, de tamaño size, a la cola con identificador msg. El cuarto parámetro
  sirve para controlar el nivel de ocupación de la cola */
  /* Introducción de datos en la cola */
  if(msgsnd(msg1,&time_msg,sizeof(time_msg),0) == -1)
  {
    perror("msgsnd");
    exit(EXIT_FAILURE);
  }
}while(time_msg.mtext != 0);
}
/* Fin función principal */
/* Función que proporciona el identificador de la cola de mensaje */
int crearcola(int key)

{
int msgqid;
/* int msgget(int ident, int flag): proporciona un identificador para la cola de clave ident,
con
permisos flag (máscara de bits) */
switch(msgqid = msgget(key, IPC_CREAT|0666))
{
/* IPC_CREAT, instrucción al sistema para crear la cola si todavía no existe */
case -1:
perror("msgget");
exit(EXIT_FAILURE);
default:
return msgqid;
}
} /* Fin función auxiliar */
